#include "mini_rt.h"

bool	lambertian_scatter(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation,
		t_ray *scattered)
{
	return (false);
}

bool	metal_scatter(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation,
		t_ray *scattered)
{
	t_vec3	refected;
	t_vec3	unit_vector;

	refected = vec3_reflect(r_in->direc, rec->normal);
	unit_vector = vec3_unit(refected);
	refected = vec3_add_vecs(refected, vec3_mul_vec(vec3_random_unit_vector(),
				rec->material->fuzz));
	scattered->orig = rec->p;
	scattered->direc = refected;
	*attenuation = rec->material->albedo;
	return (vec3_dot(scattered->direc, rec->normal) > 0);
}

static float	reflectance(float cosine, float ref_idx)
{
	float	r0;

	r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 *= r0;
	return (r0 + (1 - r0) * powf((1 - cosine), 5));
}

bool	dielectric_scatter(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation,
		t_ray **scattered)
{
	float	r1;
	t_vec3	unit_direction;
	float	cos_theta;
	bool	cannot_refract;
	t_vec3	direction;

	*attenuation = vec3_new(1, 1, 1);
	r1 = rec->material->ref_idx;
	if (rec->front_face)
		r1 = 1.0 / rec->material->ref_idx;
	unit_direction = vec3_unit(r_in->direc);
	cos_theta = fminf(vec3_dot(vec3_flip_minus(unit_direction), rec->normal),
			1.0);
	cannot_refract = r1 * sqrtf(1.0 - cos_theta * cos_theta) > 1.0;
	if (cannot_refract || reflectance(cos_theta, r1) > RANDOM_FLOAT)
		direction = vec3_reflect(unit_direction, rec->normal);
	else
		direction = vec3_refract(unit_direction, rec->normal, r1);
	*scattered = ray_new(&rec->p, &direction);
	return (true);
}
