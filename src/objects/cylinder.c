
#include "mini_rt.h"
#include "vars.h"

static float	assign_t_value(t_hit_cy_vars *var, t_obj *cy, t_interval *interval)
{
	var->m = var->d_dot * var->t[0] + var->x_dot;
	if (var->t[0] >= 0 && var->m >= 0.0 && var->m < cy->height
		&& interval_surrounds(interval, var->t[0]))
		return (var->t[0]);
	var->m = var->d_dot * var->t[1] + var->x_dot;
	if (var->t[1] >= 0 && var->m >= 0.0 && var->m < cy->height
		&& interval_surrounds(interval, var->t[1]))
		return (var->t[1]);
	return (-1);
}

static void	set_uv(t_hit_cy_vars *var, t_hit_record *rec, t_obj *cy)
{
	var->hit_vec = vec3_sub_vecs(rec->p, var->v);
	rec->u = (atan2f(var->hit_vec.z, var->hit_vec.x) + PI) / (2 * PI);
	rec->v = var->m / cy->height;
	rec->u = fmodf(rec->u, 1.0f);
	if (rec->u < 0) 
		rec->u += 1.0f;
	rec->v = fmodf(rec->v, 1.0f);
	if (rec->v < 0) 
		rec->v += 1.0f;
}

bool	cy_hit(t_obj *cy, t_ray *ray, t_interval *interval, t_hit_record *rec)
{
	t_hit_cy_vars	var;

	var.x = vec3_sub_vecs(ray->orig, cy->point);
	var.d_dot = vec3_dot(ray->direc, cy->normal);
	var.x_dot = vec3_dot(var.x, cy->normal);
	var.a = vec3_dot(ray->direc, ray->direc) - (var.d_dot * var.d_dot);
	var.b = 2.0 * (vec3_dot(ray->direc, var.x) - (var.d_dot * var.x_dot));
	var.c = vec3_dot(var.x, var.x) - (var.x_dot * var.x_dot) - (cy->radius
			* cy->radius);
	if (!cal_quadratic(var.a, var.b, var.c, var.t))
		return (false);
	rec->t = assign_t_value(&var, cy, interval);
	if (rec->t < 0)
		return (false);
	rec->p = ray_at(ray, rec->t);
	rec->material = &cy->material;
	var.m = var.d_dot * rec->t + var.x_dot;
	var.v = vec3_add_vecs(cy->point, vec3_mul_vec(cy->normal, var.m));
	rec->normal = vec3_unit(vec3_sub_vecs(rec->p, var.v));
	set_face_normal(*ray, rec->normal, rec);
	if (vec3_dot(rec->normal, ray->direc) > 0)
		rec->normal = vec3_mul_vec(rec->normal, -1);
	set_uv(&var, rec, cy);
	return (true);
}
