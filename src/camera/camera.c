#include "constants.h"
#include "mini_rt.h"

void camera_init(t_cam *c);
t_ray camera_get_ray(t_cam *c, int i, int j);
t_color camera_ray_color(t_info *info, t_ray ray, t_obj **world, int depth);

void camera_render(t_info *info)
{
	int j;
	int i;
	t_ray ray;
	t_color color;
	uint32_t packed_color;

	camera_init(&info->c);
	j = 0;
	ray.orig = info->c.point;
	while (j < info->c.image_height)
	{
		i = 0;
		while (i < info->c.image_width)
		{
			ray.direc = camera_get_ray(info->c, i, j);
			color = camera_ray_color(info, ray, info->obj, MAX_DEPTH);
			packed_color = (255 << 24) | ((uint8_t)(color.z * 255) << 16) | ((uint8_t)(color.y * 255) << 8) | (uint8_t)(color.x * 255);
			mlx_put_pixel(info->img, i, j, packed_color);
			++i;
		}
		++j;
	}
}

void camera_start(t_info *info, t_point point, float fov, t_vec3 orient)
{
	info->c.image_height = IMG_HEIGHT;
	info->c.image_width = IMG_WIDTH;
	info->img = mlx_new_image(info->mlx, info->c.image_width, info->c.image_height);
	if (!info->img || mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
		free_all(info);
	camera_render(info);
}

void camera_resize_screen(t_info *info, int image_width, int image_height)
{
	if (image_height < MAX_HEIGHT)
		info->c.image_height = image_height / 8 * 8;
	if (image_height < MAX_WIDTH)
		info->c.image_width = image_width / 8 * 8;
	if (!mlx_resize_image(info->img, info->c.image_width, info->c.image_height))
		free_all(info);
	camera_render(info);
}

void camera_move(t_info *info, t_point point, float fov, t_vec3 orient)
{
	info->c.point = point;
	info->c.fov = fov;
	info->c.orient = orient;
	camera_render(info);
}
