#include "mini_rt.h"

bool	pl_hit(t_obj *plane, t_ray *ray, t_interval *interval,
		t_hit_record *rec)
{
	t_vec3 plane_ray_vec;
	float dot_plane;
	float result;

	dot_plane = vec3_dot(ray->direc, plane->normal);
	if (dot_plane == 0)
		return (false);
	plane_ray_vec = vec3_copy(plane->point);
	plane_ray_vec = vec3_sub_vecs(plane_ray_vec, ray->orig);
	result = vec3_dot(plane_ray_vec, plane->normal);
	result = result / dot_plane;
	if (!interval_surrounds(interval, result))
		return (false);
	rec->t = result;
	rec->p = ray_at(ray, result);
	rec->normal = plane->normal;
	if (vec3_dot(rec->normal, ray->direc) > 0)
		rec->normal = vec3_mul_vec(rec->normal, -1);
	rec->material = &plane->material;
	return (true);
}