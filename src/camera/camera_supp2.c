#include "mini_rt.h"
#include "vars.h"

// @details the ambient part of phong's model.
t_color	get_phong_ambient(t_info *info)
{
	t_color	a_light;

	a_light = info->a.rgb;
	a_light = vec3_mul_vec(a_light, info->a.ratio);
	return (a_light);
}

// @details
//
// Implements the Phong reflection model
// https://en.wikipedia.org/wiki/Phong_reflection_model
// to calculate the Diffuse Light + Specular Light.
t_color	get_phong_color(t_info *info, t_get_light_vars *var)
{
	float	intensity;
	float	spec_intensity;
	t_color	res;
	t_vec3	reflect_dir;

	intensity = fmaxf(vec3_dot(var->cam_rec->normal, var->shadow_ray.direc), 0);
	res = vec3_mul_vec(var->shadow_rec.material->texture_get_color(info,
				var->shadow_rec.material, &var->shadow_rec), intensity);
	if (intensity != 0)
	{
		reflect_dir = vec3_unit(vec3_sub_vecs(var->shadow_ray.direc,
					vec3_mul_vec(var->cam_rec->normal, 2.0 * intensity)));
		spec_intensity = powf(fmaxf(vec3_dot(var->cam_ray->direc, reflect_dir),
					0), SHININESS);
		res = vec3_add_vecs(res, vec3_mul_vec(var->shadow_rec.material->albedo,
					spec_intensity));
	}
	return (res);
}
