#include "mini_rt.h"
#include "vars.h"

// @details the ambient part of phong's model.
t_color	get_ambient_light(t_info *info)
{
	t_color	a_light;

	a_light = vec3_copy(info->a.rgb);
	a_light = vec3_mul_vec(a_light, info->a.ratio);
	return (a_light);
}

// @details
// Implements the Phong reflection model for diffuse materail.
// https://en.wikipedia.org/wiki/Phong_reflection_model
// Diffuse Light + Specular Light.
t_color	get_light_color(t_info *info, t_get_light_vars *var)
{
	float	intensity;
	float	spec_intensity;
	t_color	res;
	t_vec3	reflect_dir;

	intensity = fmaxf(vec3_dot(var->cam_rec->normal, var->shadow_ray.direc), 0);
	res = vec3_mul_vec(var->shadow_rec->material->albedo, intensity);
	reflect_dir = vec3_unit(vec3_sub_vecs(var->shadow_ray.direc,
		vec3_mul_vec(var->cam_rec->normal, 2.0 * intensity)));
	spec_intensity = powf(fmaxf(vec3_dot(var->cam_ray->direc, reflect_dir), 0), SHININESS);
	res = vec3_add_vecs(res, vec3_mul_vec(var->shadow_rec.material->albedo, spec_intensity));
	return (res);
}
