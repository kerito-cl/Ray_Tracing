#include "mini_rt.h"
#include "vars.h"

bool	sp_hit(t_obj *sphere, t_ray *ray, t_interval interval, t_hit_record *rec)
{
	t_sp_hit_vars vars;

    vars.oc = vec3_sub_vecs(sphere->point, ray->orig);
	vars.a = vec3_length_squared(ray->direc);
    vars.c = vec3_length_squared(vars.oc) - sphere->radius * sphere->radius;
	vars.h = vec3_dot(ray->direc, vars.oc);
	vars.discriminant = vars.h * vars.h - vars.a * vars.c;
	if (vars.discriminant < 0)
		return (false);
	vars.sqrtd = sqrtf(vars.discriminant);
	vars.root = (vars.h - vars.sqrtd) / vars.a;
	if (!interval_surrounds(interval, vars.root))
	{
		vars.root = (vars.h + vars.sqrtd) / vars.a;
		if (!interval_surrounds(interval, vars.root))
			return (false);
	}
	rec->t = vars.root;
	rec->p = ray_at(&ray, vars.root);
	vars.outward_normal = vec3_div_vec(vec3_sub_vecs(rec->p, sphere->point), sphere->radius);
	rec->material = sphere->material;
	set_face_normal(ray, &vars.outward_normal, rec);
	return (true);
}
