#include "../include/mini_rt.h"

void	camera_init(t_cam *c)
{
	c->dist = vec3_sub_vecs(c->point, c->look_at);
	c->focal_length = vec3_length(c->dist);
	c->viewport_height = 2.0 * tanf(DTR(c->fov / 2)) * c->focal_length;
	c->viewport_width = c->aspect_ratio * c->viewport_height;
	c->w = vec3_unit(c->dist);
	c->u = vec3_unit(vec3_cross(c->orient, c->w));
	c->v = vec3_cross(c->w, c->u);
	c->viewpoint_u = vec3_mul_vec(c->u, c->viewport_width);
	c->viewpoint_v = vec3_mul_vec(c->v, c->viewport_height);
	c->pixel_delta_u = vec3_div_vec(c->viewpoint_u, c->image_width);
	c->pixel_delta_v = vec3_div_vec(c->viewpoint_v, c->image_height);
	c->top_left = vec3_add_vecs(vec3_sub_vecs(vec3_sub_vecs(c->point,
					vec3_mul_vec(c->w, c->focal_length)),
				vec3_div_vec(c->viewpoint_u, 2)), vec3_div_vec(c->viewpoint_v,
				2));
	c->pixel00_loc = vec3_add_vecs(c->top_left,
			vec3_mul_vec(vec3_add_vecs(c->pixel_delta_u, c->pixel_delta_v),
				0.5));
}

t_ray	camera_get_ray(t_cam *c, int i, int j)
{
	t_ray	ray;
	t_vec3	pixel_sample;

	pixel_sample = vec3_sub_vecs(vec3_add_vecs(c->pixel00_loc,
				vec3_mul_vec(c->pixel_delta_u, i)),
			vec3_mul_vec(c->pixel_delta_v, j));
	ray.orig = c->point;
	ray.direc = vec3_sub_vecs(pixel_sample, c->point);
	return (ray);
}

t_color camera_ray_color(t_ray *ray, t_obj **world, int depth)
{
    return vec3_new(1, 1, 1);
}

void	camera_render(t_info *info)
{
    camera_init(&info->c);
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
