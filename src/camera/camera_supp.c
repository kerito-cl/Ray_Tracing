#include "mini_rt.h"

// @details
// look_at = point + orint
// fov = 2 * arctan( tan(hov / 2) / aspect_ratio )
// w = - orint
// u = unit(cross(vup, w));
// v = cross(w, u);
// vup = -(cross(unit(cross((0, 1, 0), w)), w))
//  - When the vup is 0, 1, 0, the vup = v.
//  - So we calculate the vup by assuming the vup = 0, 1, 0,
//  - then the v value will be the vup.
// viewpoint_height = 2 * tan(fov / 2) * focal_length
// pixel_delta_u = viewpoint_u / image_width
// top_left = look_at - viewpoint_u / 2 - viewpoint_v / 2
// pixel00_loc = top_left and shift by half pixel.
void	camera_init(t_cam *c)
{
	c->look_at = vec3_add_vecs(c->point, c->orient);
	c->aspect_ratio = (float)c->image_width / c->image_height;
	c->fov = 2.0f * atanf(tanf(DTR(c->hov) / 2) / c->aspect_ratio) * (180.0f
			/ PI);
	c->w = vec3_flip_minus(c->orient);
	c->right = vec3_unit(vec3_cross(vec3_new(0, 1, 0), c->w));
	c->vup = vec3_flip_minus(vec3_cross(c->right, c->w));
	c->dist = vec3_sub_vecs(c->point, c->look_at);
	c->focal_length = vec3_length(c->dist);
	c->viewport_height = 2.0 * tanf(DTR(c->fov) / 2) * c->focal_length;
	c->viewport_width = c->aspect_ratio * c->viewport_height;
	c->u = vec3_unit(vec3_cross(c->vup, c->w));
	c->v = vec3_cross(c->w, c->u);
	c->viewpoint_u = vec3_mul_vec(c->u, c->viewport_width);
	c->viewpoint_v = vec3_flip_minus(vec3_mul_vec(c->v, c->viewport_height));
	c->pixel_delta_u = vec3_div_vec(c->viewpoint_u, c->image_width);
	c->pixel_delta_v = vec3_div_vec(c->viewpoint_v, c->image_height);
	c->top_left = vec3_sub_vecs(c->look_at,
			vec3_add_vecs(vec3_div_vec(c->viewpoint_u, 2),
				vec3_div_vec(c->viewpoint_v, 2)));
	c->pixel00_loc = vec3_add_vecs(c->top_left,
			vec3_mul_vec(vec3_add_vecs(c->pixel_delta_u, c->pixel_delta_v),
				0.5));
}

// @details
// pixel_sample: since a pixel represents an area, not a single point,
//   we start from pixel00_loc, center of the top-left pixel in the image plane.
//   then the shift based on i and j, scaling by the number of world space units
//   per image plane pixel.
t_ray	camera_get_ray(t_cam *c, int i, int j)
{
	t_ray	ray;
	t_vec3	pixel_sample;

	pixel_sample = vec3_add_vecs(vec3_add_vecs(c->pixel00_loc,
				vec3_mul_vec(c->pixel_delta_u, i)),
			vec3_mul_vec(c->pixel_delta_v, j));
	ray.orig = c->point;
	ray.direc = vec3_unit(vec3_sub_vecs(pixel_sample, c->point));
	return (ray);
}

t_color	camera_send_shadow_rays(t_info *info, t_ray *ray, t_hit_record *rec)
{
	t_ray			new_ray;
	t_hit_record	new_rec;
	t_interval		interval;
	t_color			color;

	new_ray.orig = rec->p;
	new_ray.direc = vec3_unit(vec3_sub_vecs(info->l.point, rec->p));
	interval = interval_default();
	interval.max = vec3_dot(new_ray.direc, vec3_sub_vecs(info->l.point, rec->p));
	if (world_hit_shadow(info, &new_ray, &new_rec, &interval))
		return (vec3_add_vecs(vec3_new(0, 0, 0), get_ambient_light(info)));
	color = vec3_mul_colors(rec->material->albedo, get_light_color(info, rec,
				&new_ray, ray));
	return (color);
}

// @details Monte Carlo Path Tracing is applied for calculating the reflection.
t_color	camera_send_reflect_rays(t_info *info, t_ray *ray, t_hit_record *rec,
		int depth)
{
	t_ray	scattered;
	t_color	attenuation;

	if (rec->material->scatter(ray, rec, &attenuation, &scattered))
		return (vec3_mul_vecs(camera_ray_color(info, scattered, &info->obj,
					depth - 1), attenuation));
	return (vec3_new(0, 0, 0));
}

// @brief to calculate the color of a ray.
//
// If a ray hits nothing, then it's the sky.
// If a ray hits a diffuse material
//   - calculate the color by sending shadow rays.
// If a ray hits a metal or glass
//   - calculate the color by sending refection rays.
//
// @param info: the pointer to the state of the program.
// @param ray: the ray to calculate.
// @param world: the objects.
// @param depth: the rest depth of recursive call.
// @return the color.
t_color	camera_ray_color(t_info *info, t_ray ray, t_obj **world, int depth)
{
	t_hit_record	rec;
	t_interval		interval;
	t_color			res;

	if (depth <= 0)
		return (vec3_new(0, 0, 0));
	interval = interval_default();
	if (world_hit(info, &ray, &rec, &interval))
	{
		if (rec.material->type_material == DIFFUSE)
			return (camera_send_shadow_rays(info, &ray, &rec));
		else
			return (camera_send_reflect_rays(info, &ray, &rec, depth));
	}
	return (vec3_sky());
}
