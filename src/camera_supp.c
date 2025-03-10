#include "mini_rt.h"

void	camera_init(t_cam *c)
{
	c->aspect_ratio = (float)c->image_width / c->image_height;
	c->dist = vec3_sub_vecs(c->point, c->look_at);
	c->focal_length = vec3_length(c->dist);
	c->viewport_height = 2.0 * tanf(DTR(c->fov) / 2) * c->focal_length;
	c->viewport_width = c->aspect_ratio * c->viewport_height;
	c->w = vec3_unit(vec3_sub_vecs(c->point, c->look_at));
	c->u = vec3_unit(vec3_cross(c->orient, c->w));
	c->v = vec3_cross(c->w, c->u);
	c->viewpoint_u = vec3_mul_vec(c->u, c->viewport_width);
	c->viewpoint_v = vec3_flip_minus(vec3_mul_vec(c->v, c->viewport_height));
	c->pixel_delta_u = vec3_div_vec(c->viewpoint_u, c->image_width);
	c->pixel_delta_v = vec3_div_vec(c->viewpoint_v, c->image_height);
	c->top_left = vec3_sub_vecs(c->point, vec3_add_vecs(vec3_mul_vec(c->w,
					c->focal_length), vec3_add_vecs(vec3_div_vec(c->viewpoint_u,
						2), vec3_div_vec(c->viewpoint_v, 2))));
	c->pixel00_loc = vec3_add_vecs(c->top_left,
			vec3_mul_vec(vec3_add_vecs(c->pixel_delta_u, c->pixel_delta_v),
				0.5));
}

t_ray	camera_get_ray(t_cam *c, int i, int j)
{
	t_ray	ray;
	t_vec3	pixel_sample;

	pixel_sample = vec3_add_vecs(vec3_add_vecs(c->pixel00_loc,
				vec3_mul_vec(c->pixel_delta_u, i)),
			vec3_mul_vec(c->pixel_delta_v, j));
	ray.orig = c->point;
	ray.direc = vec3_sub_vecs(pixel_sample, c->point);
	return (ray);
}

t_color	camera_send_shadow_rays(t_info *info, t_ray *ray, t_hit_record *rec)
{
	t_ray			new_ray;
	t_vec3			dist;
	t_hit_record	new_rec;
	t_interval		interval;

	vec3_normalize(&rec->p);
	new_ray.orig = rec->p;
	dist = vec3_sub_vecs(info->l.point, rec->p);
	vec3_normalize(&dist);
	new_ray.direc = dist;
	interval = interval_empty();
	if (world_hit(info, ray, rec, &interval) && rec->material.)
		return (cal_light_color()); // required.
	return (cal_shadow_light_color());
	/**
	while (i < info->lights_count) // required.
	{
		ray->orig = rec->p;
		ray->direc = vec3_normalize(vec3_sub_vecs(info->lights[i].point,
					rec->p)); // do we have this?
		if (!world_hit_without_light(info, ray, rec, &interval))   // required.
			return (cal_light_color()); // required.
		++i;
	return (cal_shadow_light_color()); // required.
	*/
}

t_color	camera_send_reflect_rays(t_info *info, t_ray *ray, t_hit_record *rec,
		int depth)
{
	t_ray	scattered;
	t_color	attenuation;

	if (rec->material->scatter(ray, rec, &attenuation, &scattered))
		return (vec3_mul_vecs(camera_ray_color(info, &scattered, info->obj,
					depth - 1), attenuation));
	return (vec3_new(0, 0, 0));
}

t_color	camera_ray_color(t_info *info, t_ray *ray, t_obj **world, int depth)
{
	t_hit_record rec;
	t_interval interval;

	if (depth <= 0)
		return (vec3_new(0, 0, 0));
	interval = interval_default;
	if (world_hit(info, ray, &rec, &interval))
	{
		if (rec.material == DIFFUSE)
			return (camera_send_shadow_rays(nfo, ray, &rec));
		else if (rec.material == LIGHT)
			return (cal_light_color()); // required.
		else
			return (camera_send_reflect_rays(info, ray, &rec, depth));
	}
	return (cal_sky_color()); // required.
}