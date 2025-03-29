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
struct timeval start, end;

t_thread_pool pool;


void *thr_draw(void *param)
{
	t_thrdata *thr;
	int row;
	int col;
	t_cam cam;
	int last_frame;
	t_info *info;

	thr = (t_thrdata *)param;
	last_frame = 0;
	info = thr->thr_info;
	while (1)
	{
        while (atomic_load(&pool.work_available) == last_frame)
			usleep(2000);
		last_frame = atomic_load(&pool.work_available);
		row = 0;
		//cam = thr->thr_info->c; NOT SURE ABOUT THIS, MAYBE IS SAFE TO USE IT
		while (row < thr->thr_info->c.image_height)
		{
			col = thr->start_row;
			while (col < thr->thr_info->c.image_width)
			{
				thr->ray = camera_get_ray(&info->c, col, row); //THREADS READING AT SAME TIME INFO->C
				thr->color = camera_ray_color(thr->thr_info, thr->ray, &thr->thr_info->obj, MAX_DEPTH);
				thr->packed_color = get_color(thr->color);
				if (atomic_load(&pool.work_available) == -1)
					return (NULL);
				else if (atomic_load(&pool.work_available) != last_frame)
				{
					row = 0;
					col = thr->start_row;
					last_frame = atomic_load(&pool.work_available);
					//cam = thr->thr_info->c; SAFER TO USE IT?
					continue;
				}
				mlx_put_pixel(info->img, col, row, thr->packed_color);
				col+=THREADS_AMOUNT;
			}
			row++;
		}
		if (thr->start_row == 0)
		{
			gettimeofday(&end, NULL);
			printf("Render time: %ld ms\n", (end.tv_sec - start.tv_sec) * 1000L
			+ (end.tv_usec - start.tv_usec) / 1000L);
		}
	}
	return (NULL);
}

void init_thread_pool(t_info *info)
{
    int i;
	int gap;

    i = 0;
    pool.work_available = 0;
	while (i < THREADS_AMOUNT)
	{
		pool.thr_data[i].thr_info = info;
		pool.thr_data[i].start_row  = i;
		i++;
	}
	i = 0;
    while (i < THREADS_AMOUNT)
    {
        pthread_create(&pool.threads[i], NULL, thr_draw, &pool.thr_data[i]);
        i++;
    }

}

void camera_render(t_info *info) 
{
	int i;

	i = 0;
	camera_init(&info->c);
	while (i < THREADS_AMOUNT)
	{
		pool.thr_data[i].thr_info = info;
		i++;
	}
	atomic_fetch_add(&pool.work_available,1);
	gettimeofday(&start, NULL);
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
	atomic_store(&pool.work_available, 0);
	usleep(10000);
	if (image_height < MAX_HEIGHT)
		info->c.image_height = image_height / 8 * 8;
	if (image_height < MAX_WIDTH)
		info->c.image_width = image_width / 8 * 8;
	if (!mlx_resize_image(info->img, info->c.image_width, info->c.image_height))
		free_all(info);
	camera_render(info);
	//atomic_store(0)
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
}