
#include "mini_rt.h"

bool quadratic(float a, float b, float c, float *t0, float *t1)
{
    float discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0)
        return false;  // No real roots

    discriminant = sqrtf(discriminant);
    float inv2a = 0.5 / a;  // More precise division
    *t0 = (-b - discriminant) * inv2a;
    *t1 = (-b + discriminant) * inv2a;

    return true;
}

bool cy_hit(t_obj *cy, t_ray *ray, t_interval *interval, t_hit_record *rec)
{
    // Construct local basis
    /*t_vec3 x = vec3_sub_vecs(ray->orig, cy->point);
    float d_dot = vec3_dot(ray->direc, cy->normal);
    float x_dot = vec3_dot(x, cy->normal);

    t_vec3 d_proj = vec3_mul_vec(cy->normal, d_dot);
    t_vec3 x_proj = vec3_mul_vec(cy->normal, x_dot);

    t_vec3 d_perp = vec3_sub_vecs(ray->direc, d_proj);
    t_vec3 x_perp = vec3_sub_vecs(x, x_proj);

    float a = vec3_dot(d_perp, d_perp);
    float b = 2.0 * vec3_dot(d_perp, x_perp);
    float c = vec3_dot(x_perp, x_perp) - (cy->radius * cy->radius);*/

    t_vec3 x = vec3_sub_vecs(ray->orig, cy->point);
    float d_dot = vec3_dot(ray->direc, cy->normal);
    float x_dot = vec3_dot(x, cy->normal);

    float a = vec3_dot(ray->direc, ray->direc) - (d_dot * d_dot);
    float b = 2.0 * (vec3_dot(ray->direc, x) - (d_dot * x_dot));
    float c = vec3_dot(x, x) - (x_dot * x_dot) - (cy->radius * cy->radius);
    float t0, t1;
    if (t0 > t1) { float temp = t0; t0 = t1; t1 = temp; }

    // Ignore negative intersections (behind the ray)
    if (t0 < 0) t0 = t1;
    if (t0 < 0) return false;

    if (!quadratic(a, b, c, &t0, &t1))
        return false; // No intersection
    for (int i = 0; i < 2; i++)
    {
        rec->t = (i == 0) ? t0 : t1;
        float m = d_dot * rec->t + x_dot;
        if (m >= 0.0 && m <= cy->height)
        {
            if (!interval_surrounds(interval, rec->t))
                return false;
            rec->p = ray_at(ray, rec->t);

            rec->material = &cy->material;
            t_vec3 a = vec3_add_vecs(cy->point, vec3_mul_vec(cy->normal, m));
            rec->normal = vec3_sub_vecs(rec->p, a);
            rec->normal = vec3_unit(rec->normal);
            if (vec3_dot(rec->normal, ray->direc) > 0)
                rec->normal = vec3_mul_vec(rec->normal, -1);
            return true;
        }
    }
    return false;
}

