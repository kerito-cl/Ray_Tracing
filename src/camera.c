#include "mini_rt.h"

void camera_init(t_cam *c);
t_ray camera_get_ray(t_cam *c, int i, int j);
t_color camera_ray_color(t_info *info, t_ray *ray, t_obj **world, int depth);

void camera_render(t_info *info)
{
	camera_init(&info->c);
	// waiting
}

void camera_resize_screen(t_info *info, int image_width, int image_height)
{
	info->c.image_height = image_height / 8 * 8;
	info->c.image_width = image_width / 8 * 8;
	camera_render(info);
}

void camera_move(t_info *info, t_point point, float fov, t_vec3 orient)
{
	info->c.point = point;
	info->c.fov = fov;
	info->c.orient = orient;
	camera_render(info);
}
