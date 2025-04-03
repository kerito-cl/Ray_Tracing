#include "mini_rt.h"
#include "vars.h"

// @brief returns if the candidates `t` is valid.
static float	get_t(t_obj *cone, t_ray *ray, t_interval *interval, t_hit_cone_vars *var)
{
	t_point hit;
	float h;
	
	hit = ray_at(ray, var->t[0]);
	h = vec3_dot(vec3_sub_vecs(hit, cone->point), cone->normal);
	if (interval_surrounds(interval, var->t[0]) &&  h > 0 && h < cone->height)
		return (var->t[0]);
	hit = ray_at(ray, var->t[1]);
	h = vec3_dot(vec3_sub_vecs(hit, cone->point), cone->normal);
	if (interval_surrounds(interval, var->t[1]) &&  h > 0 && h < cone->height)
		return (var->t[1]);
	return (-1);
}

// @brief to set the uv for the cone.
static void set_uv(t_hit_cone_vars *var, t_hit_record *rec, t_obj *cone)
{
	t_vec3 hit_vec;
	
	hit_vec = vec3_sub_vecs(rec->p, var->p_base);
	rec->u = (atan2f(hit_vec.z, hit_vec.x) + PI) / (2 * PI);
	rec->v = var->m / cone->height;
	rec->u = fmodf(rec->u, 1.0f);
	rec->v = fmodf(rec->v, 1.0f);
	if (rec->u < 0) 
		rec->u += 1.0f;
	if (rec->v < 0) 
		rec->v += 1.0f;
	rec->uv_chess_board = false;
}

// @details returns if the given cone is hit by the given ray in given interval.
// and fill the given rec.
//
// The math is:
//
// (dot(N, X - V))² = |X - V|² * cos²θ
// - X is a point on the cone
// - V is the cone apex (tip)
// - N is the normalized axis direction (pointing from apex to base)
// - θ is the half-angle of the cone (tanθ = r / h)
//
// For a given ray:
// X(t) = ray.origin + t * ray.direction
// Substituting X into the equation and simplifying gives a quadratic:
// a·t² + b·t + c = 0
//
// The process:
// 1 Compute a, b, c.
// 2. Solve the quadratic equation for t
// 3. For each valid t in the interval:
//    - Compute the hit point and test whether it's within the height of the cone
// 4. If hit is valid:
//    - Compute the surface normal at the point
//    - Compute UV coordinates for texturing
bool	cn_hit(t_obj *cone, t_ray *ray, t_interval *interval, t_hit_record *rec)
{
	t_hit_cone_vars var;

	var.oc = vec3_sub_vecs(ray->orig, cone->point);
	var.cos2 = (cone->radius / cone->height) * (cone->radius / cone->height);
	var.d_dot_n = vec3_dot(ray->direc, cone->normal);
	var.oc_dot_n = vec3_dot(var.oc, cone->normal);
	var.d_proj = vec3_sub_vecs(ray->direc, vec3_mul_vec(cone->normal, var.d_dot_n));
	var.oc_proj = vec3_sub_vecs(var.oc, vec3_mul_vec(cone->normal, var.oc_dot_n));
	var.a = vec3_dot(var.d_proj, var.d_proj) - var.cos2 * var.d_dot_n * var.d_dot_n;
	var.b = 2.0f * (vec3_dot(var.d_proj, var.oc_proj) - var.cos2 * var.d_dot_n * var.oc_dot_n);
	var.c = vec3_dot(var.oc_proj, var.oc_proj) - var.cos2 * var.oc_dot_n * var.oc_dot_n;
	if (!cal_quadratic(var.a, var.b, var.c, var.t))
		return false;
	rec->t = get_t(cone, ray, interval, &var);
	if (rec->t < 0)
		return false;
	rec->p = ray_at(ray, rec->t);
	rec->material = &cone->material;
	var.m = vec3_dot(vec3_sub_vecs(rec->p, cone->point), cone->normal);
	var.p_base = vec3_add_vecs(cone->point, vec3_mul_vec(cone->normal, var.m));
	rec->normal = vec3_unit(vec3_sub_vecs(vec3_unit(vec3_sub_vecs(rec->p, var.p_base)), vec3_mul_vec(cone->normal, var.cos2)));
	if (vec3_dot(rec->normal, ray->direc) > 0)
		rec->normal = vec3_mul_vec(rec->normal, -1);
	set_uv(&var, rec, cone);
	return (true);
}
