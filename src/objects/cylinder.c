
#include "mini_rt.h"
#include "vars.h"

static bool	quadratic(float a, float b, float c, float *t0, float *t1)
{
	float	discriminant;
	float	inv2a;

	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (false);
	discriminant = sqrtf(discriminant);
	inv2a = 0.5 / a;
	*t0 = (-b - discriminant) * inv2a;
	*t1 = (-b + discriminant) * inv2a;
	return (true);
}
static void	assign_t_value(t_hit_cy_vars *var, t_obj *cy, t_interval *interval,
		float *t_valid)
{
	float	temp;

	if (var->t0 < 0)
		var->t0 = var->t1;
	if (var->t0 > var->t1)
	{
		temp = var->t0;
		var->t0 = var->t1;
		var->t1 = temp;
	}
	*t_valid = -1;
	var->m = var->d_dot * var->t0 + var->x_dot;
	if (var->t0 >= 0 && var->m >= 0.0 && var->m < cy->height
		&& interval_surrounds(interval, var->t0))
		*t_valid = var->t0;
	var->m = var->d_dot * var->t1 + var->x_dot;
	if (*t_valid == -1 && var->t1 >= 0 && var->m >= 0.0 && var->m < cy->height
		&& interval_surrounds(interval, var->t1))
		*t_valid = var->t1;
}

bool	cy_hit(t_obj *cy, t_ray *ray, t_interval *interval, t_hit_record *rec)
{
	t_hit_cy_vars	var;
	float			t_valid;

	var.x = vec3_sub_vecs(ray->orig, cy->point);
	var.d_dot = vec3_dot(ray->direc, cy->normal);
	var.x_dot = vec3_dot(var.x, cy->normal);
	var.a = vec3_dot(ray->direc, ray->direc) - (var.d_dot * var.d_dot);
	var.b = 2.0 * (vec3_dot(ray->direc, var.x) - (var.d_dot * var.x_dot));
	var.c = vec3_dot(var.x, var.x) - (var.x_dot * var.x_dot) - (cy->radius
			* cy->radius);
	if (!quadratic(var.a, var.b, var.c, &var.t0, &var.t1))
		return (false);
	assign_t_value(&var, cy, interval, &t_valid);
	if (t_valid == -1)
		return (false);
	rec->t = t_valid;
	rec->p = ray_at(ray, rec->t);
	rec->material = &cy->material;
	var.m = var.d_dot * rec->t + var.x_dot;
	var.v = vec3_add_vecs(cy->point, vec3_mul_vec(cy->normal, var.m));
	rec->normal = vec3_unit(vec3_sub_vecs(rec->p, var.v));
	if (vec3_dot(rec->normal, ray->direc) > 0)
		rec->normal = vec3_mul_vec(rec->normal, -1);
	var.hit_vec = vec3_sub_vecs(rec->p, var.v);
	rec->u = (atan2f(var.hit_vec.z, var.hit_vec.x) + PI) / (2 * PI);
	rec->v = var.m / cy->height;
	rec->u = fmodf(rec->u, 1.0f);
	if (rec->u < 0) 
		rec->u += 1.0f;
	rec->v = fmodf(rec->v, 1.0f);
	if (rec->v < 0) 
		rec->v += 1.0f;
	return (true);
}

/*t_vec3 x = vec3_sub_vecs(ray->orig, cy->point);
float var.d_dot = vec3_dot(ray->direc, cy->normal);
float var.x_dot = vec3_dot(x, cy->normal);

t_vec3		d_proj = vec3_mul_vec(cy->normal, var.d_dot);
t_vec3		x_proj = vec3_mul_vec(cy->normal, var.x_dot);

t_vec3		d_perp = vec3_sub_vecs(ray->direc, d_proj);
t_vec3		x_perp = vec3_sub_vecs(x, x_proj);

float		a = vec3_dot(d_perp, d_perp);
float		b = 2.0 * vec3_dot(d_perp, x_perp);
float		c = vec3_dot(x_perp, x_perp) - (cy->radius * cy->radius);*/