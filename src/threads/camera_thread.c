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

void	camera_render(t_info *info)
{
	if (atomic_load(&info->pool.abort_signal) == -1)
	{
		camera_init(&info->c);
		atomic_store(&info->pool.abort_signal, 1);
		atomic_fetch_add(&info->pool.work_available, 1);
	}
	else
	{
		atomic_store(&info->pool.abort_signal, 0);
		while (atomic_load(&info->pool.start_task) != THREADS_AMOUNT)
			usleep(1);
		camera_init(&info->c);
		atomic_store(&info->pool.abort_signal, 1);
		atomic_fetch_add(&info->pool.work_available, 1);
	}
}

void	camera_start(t_info *info)
{
	atomic_store(&info->pool.abort_signal, -1);
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
	atomic_store(&info->pool.abort_signal, 0);
	while (atomic_load(&info->pool.start_task) != THREADS_AMOUNT)
		usleep(1);
	if (image_height < MAX_HEIGHT)
		info->c.image_height = image_height / 8 * 8;
	if (image_height < MAX_WIDTH)
		info->c.image_width = image_width / 8 * 8;
	if (!mlx_resize_image(info->img, info->c.image_width, info->c.image_height))
		free_all(info);
	atomic_store(&info->pool.abort_signal, -1);
	camera_render(info);
}
