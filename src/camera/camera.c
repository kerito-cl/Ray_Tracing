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

// @details to render by iterate all the pixels.
#include <stdatomic.h> 

typedef struct s_tile_data {
    int tile_x;
    int tile_y;
} t_tile_data;


typedef struct s_tile
{
	t_thrdata *thr;
	t_info *info;
	int tile_size;
	int tiles_x;
	int total_tiles;
} t_tile;

atomic_int g_tile_index = 0;

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
		tile_id = atomic_fetch_add(&g_tile_index, 1);
		if (tile_id >= tile->total_tiles)
			break;
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
	tile.tile_size = 8;
	tile.tiles_x = tile.info->c.image_width / 8;
	tile.total_tiles =(tile.info->c.image_width / 8) * (tile.info->c.image_height / 8);
	process_tiles(&tile);
	return NULL;
}
void	init_threads(t_thrdata *thr_data ,t_info *info)
{
	int 	i;
	int 	gap;

	i = 0;
	gap = (info->c.image_height / THREADS_AMOUNT);
	while (i < THREADS_AMOUNT)
	{
		thr_data[i].thr_info = info;
		i++;
	}
}

/*void	init_threads(t_thrdata *thr_data ,t_info *info)
{
	int 	i;
	int 	gap;

	i = 0;
	gap = (info->c.image_height / THREADS_AMOUNT);
	while (i < THREADS_AMOUNT)
	{
		thr_data[i].thr_info = info;
		if (i == 0)
		{
			thr_data[i].start_row  = 0;
			thr_data[i].end_row = gap;
		}
		else
		{
			thr_data[i].start_row  = thr_data[i - 1].end_row;
			thr_data[i].end_row = thr_data[i].start_row + gap;
		}
		i++;
	}
}

void	*thr_draw(void *param)
{
	int	row;
	int	col;
	t_thrdata *thr;
	t_info *info;

	thr = (t_thrdata *)param;
	info = thr->thr_info;
	row = thr->start_row;
	int i = 0;
	while (row < thr->end_row)
	{
		col = 0;
		while (col < thr->thr_info->c.image_width)
		{
			//if (j == 524 && i == 1249)
				//break_point(i);
			thr->ray = camera_get_ray(&thr->thr_info->c, col, row);
			thr->color = camera_ray_color(thr->thr_info, thr->ray, &thr->thr_info->obj, MAX_DEPTH);
			thr->packed_color = get_color(thr->color);
			//put_pixel(info->img, col, row, thr->color);
			mlx_put_pixel(info->img, col, row, thr->packed_color);
			++col;
		}
		row++;
	}
	return (NULL);
}*/

void	camera_render(t_info *info)
{
	int			j;
	int			i;
	t_ray		ray;
	t_color		color;
	uint32_t	packed_color;
	pthread_t *thr;
	t_thrdata  *thr_data;

	struct timeval start, end;
	camera_init(&info->c);
	thr_data =	ft_calloc(sizeof(t_thrdata), THREADS_AMOUNT);
	if (thr_data == NULL)
		free_all(info);
	j = 0;
	gettimeofday(&start, NULL);
	init_threads(thr_data, info);
	thr = malloc(sizeof(pthread_t) * THREADS_AMOUNT);
	if (thr == NULL)
	{
		free(thr_data);
		free_all(info);
	}
	while (j < THREADS_AMOUNT)
	{
		if(pthread_create(&thr[j], NULL, thr_draw, thr_data + j) != 0)
			free_all(info);
		j++;
	}
	j = 0;
	while (j < THREADS_AMOUNT)
	{
		if(pthread_join(thr[j], NULL))
			free_all(info);
		j++;
	}
	g_tile_index = 0;
	gettimeofday(&end, NULL);
	printf("Render time: %ld ms\n", (end.tv_sec - start.tv_sec) * 1000L
		+ (end.tv_usec - start.tv_usec) / 1000L);
	free(thr_data);
	free(thr);
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
