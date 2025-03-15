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

// @details the diffuse part of phong's model.
t_color	handle_diffuse_light(t_info *info, t_hit_record *rec, t_ray *shadow_ray,
		t_hit_record *shadow_rec)
{
	float	intensity;

	intensity = fmaxf(vec3_dot(rec->normal, shadow_ray->direc), 0);
	return (vec3_mul_vec(shadow_rec->material->albedo, intensity));
}

// @details the specular part of phong's model.
t_color	handle_specular_light(t_info *info, t_get_light_vars *var)
{
	float	spec_intensity;
	float	intensity;
	t_vec3	reflect_dir;

	intensity = fmaxf(vec3_dot(var->cam_rec->normal, var->shadow_ray.direc), 0);
	reflect_dir = vec3_unit(vec3_sub_vecs(var->shadow_ray.direc,
				vec3_mul_vec(var->cam_rec->normal, 2.0 * intensity)));
	spec_intensity = powf(fmaxf(vec3_dot(var->cam_ray->direc, reflect_dir), 0),
			SHININESS);
	return (vec3_mul_vec(var->shadow_rec.material->albedo, spec_intensity));
}

// @details
// Implements the Phong reflection model for diffuse materail.
// https://en.wikipedia.org/wiki/Phong_reflection_model
// Ambient Light + Diffuse Light + Specular Light.
t_color	get_light_color(t_info *info, t_get_light_vars *var)
{
	t_color	res;

	res = handle_diffuse_light(info, var->cam_rec, &var->shadow_ray,
			&var->shadow_rec);
	res = vec3_add_vecs(res, handle_specular_light(info, var));
	return (res);
}
