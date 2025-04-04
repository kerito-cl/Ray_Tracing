#include "mini_rt.h"

// @details
// In this project, we don't handle the lambertian scatter.
bool	lambertian_scatter(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation,
		t_ray *scattered)
{
	return (false);
}

// @details
// 1 calculates the direction of reflection.
// 2 adds some random vector for fuzz.
// 3 the attenuation is the albedo.
// 4 be sure the refection degree is valid (not a refraction).
bool	metal_scatter(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation,
		t_ray *scattered)
{
	scattered->direc = vec3_unit(vec3_reflect(r_in->direc, rec->normal));
	scattered->direc = vec3_add_vecs(scattered->direc,
			vec3_mul_vec(vec3_random_unit_vector(), rec->material->fuzz));
	scattered->orig = rec->p;
	scattered->type = REFECTION_RAY;
	*attenuation = rec->material->albedo;
	return (vec3_dot(scattered->direc, rec->normal) > 0);
}

// @details
// Implements Schlick's approximation to calculate reflectance.
// When the incident angle is near 90 degrees, more light is reflected.
static float	reflectance(float cosine, float ref_idx)
{
	float	r0;

	r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 *= r0;
	return (r0 + (1 - r0) * powf((1 - cosine), 5));
}

// @details
// implements the Fresnel Equations, and Snell's Law.

// 1 the attenuation is always white, because we don't change the color.
// 2 r1: the possiblity of the refection.
// 3 cos_theta: the incident angle.
// 4 cannot_refract: Snell's Law, if there is refract,
//  - light is from glass to air, and incident angle > 90.
// 5 light is either reflected or refracted depending on the probability,
bool	dielectric_scatter(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation,
		t_ray *scattered)
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
	direction = vec3_refract(unit_direction, rec->normal, r1);
	scattered->orig = rec->p;
	scattered->direc = direction;
	scattered->type = REFECTION_RAY;
	return (true);
}

// @details
// for light, just sets the attenuation and returns false.
bool	light_scatter(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation,
		t_ray *scattered)
{
	*attenuation = rec->material->albedo;
	return (true);
}
