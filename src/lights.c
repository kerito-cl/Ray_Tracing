#include "mini_rt.h"

// @details the ambient part of phong's model.
t_color	get_ambient_light(t_info *info)
{
	t_color	a_light;

	a_light = vec3_copy(info->a.rgb);
	a_light = vec3_mul_vec(a_light, info->a.ratio);
	return (a_light);
}

// @details the diffuse part of phong's model.
t_color	handle_diffuse_light(t_info *info, t_hit_record *rec, t_ray *shadow_ray)
{
	float	intensity;

	intensity = fmaxf(vec3_dot(rec->normal, shadow_ray->direc), 0);
	return (vec3_mul_vec(info->l.rgb, intensity));
}

// @details the specular part of phong's model.
t_color	handle_specular_light(t_info *info, t_hit_record *rec,
		t_ray *shadow_ray, t_ray *cam_ray)
{
	float	spec_intensity;
	float	intensity;
	t_vec3	reflect_dir;

	intensity = fmaxf(vec3_dot(rec->normal, shadow_ray->direc), 0);
	reflect_dir = vec3_unit(vec3_sub_vecs(shadow_ray->direc,
				vec3_mul_vec(rec->normal, 2.0 * intensity)));
	spec_intensity = powf(fmaxf(vec3_dot(cam_ray->direc, reflect_dir), 0),
			SHININESS);
	return (vec3_mul_vec(info->l.rgb, spec_intensity));
}

// @details
// Implements the Phong reflection model for diffuse materail.
// https://en.wikipedia.org/wiki/Phong_reflection_model
// Ambient Light + Diffuse Light + Specular Light.
t_color	get_light_color(t_info *info, t_hit_record *rec, t_ray *shadow_ray,
		t_ray *cam_ray)
{
	t_color	res;

	res = get_ambient_light(info);
	res = vec3_add_vecs(res, handle_diffuse_light(info, rec, shadow_ray));
	res = vec3_add_vecs(res, handle_specular_light(info, rec, shadow_ray,
				cam_ray));
	return (res);
}
