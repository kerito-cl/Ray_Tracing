#include "mini_rt.h"

bool    lambertian_scatter(t_material *mat, t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered)
{
    return (false);
}

bool    metal_scatter(t_material *mat, t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered)
{
    t_vec3 refected = vec3_reflect(r_in->direction, &rec->normal);
    t_vec3 unit_vector = vec3_unit(&refected);
    t_vec3 rand = vec3_random_unit_vector();
    t_vec3 temp = vec3_mul_vec(&rand, mat->fuzz);
    refected = vec3_add_vecs(&refected, &temp);
    *scattered = ray_new(&rec->p, &refected);
    *attenuation = mat->albedo;
    return vec3_dot((*scattered)->direction, &rec->normal) > 0;
    return (false);
}

tatic float reflectance(float cosine, float ref_idx)
{
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 *= r0;
    return r0 + (1 - r0) * powf((1 - cosine), 5);
}

bool dielectric_scatter(t_material *mat, t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray **scattered)
{
    *attenuation = vec3_new(1, 1, 1);
    float r1 = rec->front_face ? (1.0 / mat->ref_idx) : mat->ref_idx;

    t_vec3 unit_direction = vec3_unit(r_in->direction);
    t_vec3 neg_unit_direction = vec3_flip_minus(&unit_direction);

    float cos_theta = fminf(vec3_dot(&neg_unit_direction, &rec->normal), 1.0);
    float sin_theta = sqrtf(1.0 - cos_theta * cos_theta);

    bool cannot_refract = r1 * sin_theta > 1.0;
    t_vec3 direction;

    if (cannot_refract || reflectance(cos_theta, r1) > RANDOM_FLOAT)
        direction = vec3_reflect(&unit_direction, &rec->normal);
    else
        direction = vec3_refract(&unit_direction, &rec->normal, r1);

    *scattered = ray_new(&rec->p, &direction);
    return true;
}

