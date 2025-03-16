#include "mini_rt.h"
#include "vars.h"

static float	quadratic(float a, float b, float c)
{
	float	discriminant;
	float	t0;
	float	t1;

	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (INFINITY);
	discriminant = sqrtf(discriminant);
	t0 = (-b - discriminant) * (1 / (2 * a));
	t1 = (-b + discriminant) * (1 / (2 * a));
	if (t0 > 0)
		return (t0);
	if (t1 > 0)
		return (t1);
	return (INFINITY);
}

float	intersect_sphere(t_ray ray, t_obj *sp)
{
	t_vec3	l;
	float	a;
	float	b;
	float	c;

	l = ray.orig;
	l = vec3_sub_vecs(l, sp->point);
	a = vec3_dot(ray.direc, ray.direc);
	b = 2 * vec3_dot(l, ray.direc);
	c = vec3_dot(l, l) - (sp->radius * sp->radius);
	return (quadratic(a, b, c));
}

bool	sp_hit2(t_obj *sphere, t_ray *ray, t_interval *interval,
		t_hit_record *rec)
{
	t_sp_hit_vars	vars;

	if (sphere->material.type_material == LIGHT && ((!LIGHT_VISIBLE
		&& ray->type == CAM_RAY) || ray->type == REFECTION_RAY))
		return (false);
	vars.root = intersect_sphere(*ray, sphere);
	if (!interval_surrounds(interval, vars.root))
	{
		vars.root = (vars.h + vars.sqrtd) / vars.a;
		if (!interval_surrounds(interval, vars.root))
			return (false);
	}
	rec->t = vars.root;
	rec->p = ray_at(ray, vars.root);
	vars.outward_normal = vec3_div_vec(vec3_sub_vecs(rec->p, sphere->point),
			sphere->radius);
	rec->material = &sphere->material;
	set_face_normal(*ray, vars.outward_normal, rec);
	rec->normal_2 = vec3_sub_vecs(rec->p, sphere->point);
	return (true);
}

bool	sp_hit(t_obj *sphere, t_ray *ray, t_interval *interval,
		t_hit_record *rec)
{
	t_sp_hit_vars	vars;

	if (sphere->material.type_material == LIGHT && ((!LIGHT_VISIBLE
		&& ray->type == CAM_RAY) || ray->type == REFECTION_RAY))
		return (false);
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
	rec->p = ray_at(ray, vars.root);
	vars.outward_normal = vec3_div_vec(vec3_sub_vecs(rec->p, sphere->point),
			sphere->radius);
	rec->material = &sphere->material;
	set_face_normal(*ray, vars.outward_normal, rec);
	return (true);
}
