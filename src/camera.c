#include "constants.h"
#include "mini_rt.h"

void	camera_init(t_cam *c);
t_ray	camera_get_ray(t_cam *c, int i, int j);
t_color	camera_ray_color(t_info *info, t_ray ray, t_obj **world, int depth);

void	camera_render(t_info *info)
{
	int		j;
	int		i;
	t_ray	ray;
	t_vec3	target;

	camera_init(&info->c);
	j = 0;
	ray.orig = info->c.point;
	while (j < info->c.image_height)
	{
		i = 0;
		while (i < info->c.image_width)
		{
			target = vec3_new(i, j, info->c.focal_length);
			vec3_normalize(&target);
			ray.direc = target;
			info->screen[j][i] = camera_ray_color(info, ray, info->obj,
					MAX_DEPTH);
			++i;
		}
		++j;
	}
}

void	camera_resize_screen(t_info *info, int image_width, int image_height)
{
	info->c.image_height = image_height / 8 * 8;
	info->c.image_width = image_width / 8 * 8;
	camera_render(info);
}

void	camera_move(t_info *info, t_point point, float fov, t_vec3 orient)
{
	info->c.point = point;
	info->c.fov = fov;
	info->c.orient = orient;
	camera_render(info);
}
