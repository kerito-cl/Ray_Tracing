#include "constants.h"
#include "mini_rt.h"
#include <sys/time.h>

void			camera_init(t_cam *c);
t_ray			camera_get_ray(t_cam *c, int i, int j);
t_color			camera_ray_color(t_info *info, t_ray ray, t_obj **world,
					int depth);

unsigned int	get_color(t_vec3 vec)
{
	return (((uint8_t)(vec.x * 255) << 24) | ((uint8_t)(vec.y
				* 255) << 16) | ((uint8_t)(vec.z * 255) << 8) | 255);
}

void	break_point(int i)
{
	printf("%d\n", i);
	return ;
}

t_thread_pool pool;

void render_tile(t_tile *tile, int tile_x, int tile_y)
{
	int	row;
	int	col;

	row = tile_y;
	while (row < tile_y + tile->tile_size)
	{
		col = tile_x;
		while (col < tile_x + tile->tile_size)
		{
			if (row < tile->info->c.image_height && col < tile->info->c.image_width)
			{
				tile->thr->ray = camera_get_ray(&tile->info->c, col, row);
				tile->thr->color = camera_ray_color(tile->info, tile->thr->ray, &tile->info->obj, MAX_DEPTH);
				tile->thr->packed_color = get_color(tile->thr->color);
				mlx_put_pixel(tile->info->img, col, row, tile->thr->packed_color);
			}
			col++;
		}
		row++;
	}
}

void process_tiles(t_tile *tile)
{
    int tile_id;
    int tile_x;
    int tile_y;

    while (1) 
	{
        pthread_mutex_lock(&pool.mutex);
        while (!pool.work_available)
            pthread_cond_wait(&pool.condition, &pool.mutex);
        tile_id = atomic_fetch_add(&pool.tile_index, 1);
        if (tile_id >= tile->total_tiles)
        {
            pthread_mutex_unlock(&pool.mutex);
            pthread_mutex_lock(&pool.mutex);
			pool.work_available = 0;
            pthread_mutex_unlock(&pool.mutex);
            continue;
        }
        pthread_mutex_unlock(&pool.mutex);
        tile_x = (tile_id % tile->tiles_x) * tile->tile_size;
        tile_y = (tile_id / tile->tiles_x) * tile->tile_size;
        render_tile(tile, tile_x, tile_y);
    }
}

void *thr_draw(void *param)
{
	t_thrdata *thr;
	t_tile tile;

	thr = (t_thrdata *)param;
	tile.thr = thr;
	tile.info = thr->thr_info;
	tile.tile_size = TILE_SIZE;
	tile.tiles_x = tile.info->c.image_width / TILE_SIZE;
	tile.total_tiles =(tile.info->c.image_width / TILE_SIZE) * (tile.info->c.image_height / TILE_SIZE);
	process_tiles(&tile);
	return NULL;
}

void init_thread_pool(t_info *info)
{
    int i;

    i = 0;
    pool.tile_index = 0;
    pool.work_available = 0;
    pthread_mutex_init(&pool.mutex, NULL);
    pthread_cond_init(&pool.condition, NULL);
    while (i < THREADS_AMOUNT)
    {
        pool.thr_data[i].thr_info = info;
        pthread_create(&pool.threads[i], NULL, thr_draw, &pool.thr_data[i]);
        i++;
    }
}

void start_render_task()
{
    pthread_mutex_lock(&pool.mutex);
    pool.tile_index = 0;
    pool.work_available = 1;
    pthread_cond_broadcast(&pool.condition);
    pthread_mutex_unlock(&pool.mutex);
}

void camera_render(t_info *info) {
    struct timeval start, end;
    gettimeofday(&start, NULL);

    pthread_mutex_lock(&pool.mutex);
	camera_init(&info->c);
    pthread_mutex_unlock(&pool.mutex);
    start_render_task(); 
    gettimeofday(&end, NULL);
    printf("Render time: %ld ms\n", (end.tv_sec - start.tv_sec) * 1000L + (end.tv_usec - start.tv_usec) / 1000L);
}

void	camera_start(t_info *info)
{
	info->c.image_height = IMG_HEIGHT;
	info->c.image_width = IMG_WIDTH;
	info->mlx = mlx_init(IMG_WIDTH, IMG_HEIGHT, "KD MiniRT", true);
	info->img = mlx_new_image(info->mlx, info->c.image_width,
			info->c.image_height);
	if (!info->img || mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
		free_all(info);
	init_thread_pool(info);
	camera_render(info);
}

void	camera_resize_screen(t_info *info, int image_width, int image_height)
{
	if (image_height < MAX_HEIGHT)
		info->c.image_height = image_height / 8 * 8;
	if (image_height < MAX_WIDTH)
		info->c.image_width = image_width / 8 * 8;
	if (!mlx_resize_image(info->img, info->c.image_width, info->c.image_height))
		free_all(info);
	camera_render(info);
}

void destroy_thread_pool() {
    int i;

    i = 0;
    while (i < THREADS_AMOUNT) 
    {
        pthread_cancel(pool.threads[i]); 
        pthread_join(pool.threads[i], NULL);
        i++;
    }
	pthread_mutex_destroy(&pool.mutex);
    pthread_cond_destroy(&pool.condition);
}