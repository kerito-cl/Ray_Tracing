
#include "vars.h"
#include "mini_rt.h"

bool quadratic(float a, float b, float c, float *t0, float *t1)
{
    float   discriminant;
    float   inv2a;

    discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0)
        return false;
    discriminant = sqrtf(discriminant);
    inv2a = 0.5 / a;
    *t0 = (-b - discriminant) * inv2a;
    *t1 = (-b + discriminant) * inv2a;
    return true;
}

bool cy_hit(t_obj *cy, t_ray *ray, t_interval *interval, t_hit_record *rec)
{
    t_hit_cy_vars var;
    int i;

    var.x = vec3_sub_vecs(ray->orig, cy->point);
    var.d_dot = vec3_dot(ray->direc, cy->normal);
    var.x_dot = vec3_dot(var.x, cy->normal);
    var.a = vec3_dot(ray->direc, ray->direc) - (var.d_dot * var.d_dot);
    var.b = 2.0 * (vec3_dot(ray->direc, var.x) - (var.d_dot * var.x_dot));
    var.c = vec3_dot(var.x, var.x) - (var.x_dot * var.x_dot) - (cy->radius * cy->radius);
    if (!quadratic(var.a, var.b, var.c, &var.t0, &var.t1))
        return false;
    i = 0;
    if (var.t0 < 0)
        var.t0 = var.t1;
    if (var.t0 > var.t1)
    {
        float temp = var.t0;
        var.t0 = var.t1;
        var.t1 = temp;
    }
    float t_valid = -1;
    var.m = var.d_dot * var.t0 + var.x_dot;
    if (var.t0 >= 0 && var.m >= 0.0 && var.m < cy->height && interval_surrounds(interval, var.t0))
        t_valid = var.t0;
    var.m = var.d_dot * var.t1 + var.x_dot;
    if (t_valid == -1 && var.t1 >= 0 && var.m >= 0.0 && var.m < cy->height && interval_surrounds(interval, var.t1))
        t_valid = var.t1;

    if (t_valid == -1)
        return false;

    rec->t = t_valid;
    rec->p = ray_at(ray, rec->t);
    rec->material = &cy->material;
    var.m = var.d_dot * rec->t + var.x_dot;
    var.v = vec3_add_vecs(cy->point, vec3_mul_vec(cy->normal, var.m));
    rec->normal = vec3_unit(vec3_sub_vecs(rec->p, var.v));

    // Ensure normal points against the ray
    if (vec3_dot(rec->normal, ray->direc) > 0)
        rec->normal = vec3_mul_vec(rec->normal, -1);

    return true;
    /*while (i < 2)
    {
        if (i == 0)
            rec->t = var.t0;
        else
            rec->t = var.t1;
        var.m = var.d_dot * rec->t + var.x_dot;
        if (var.m >= 0.0 && var.m <= cy->height)
        {
            if (!interval_surrounds(interval, rec->t))
                return false;
            rec->p = ray_at(ray, rec->t);
            rec->material = &cy->material;
            var.v = vec3_add_vecs(cy->point, vec3_mul_vec(cy->normal, var.m));
            rec->normal = vec3_sub_vecs(rec->p, var.v);
            rec->normal = vec3_unit(rec->normal);
            if (vec3_dot(rec->normal, ray->direc) > 0)
                rec->normal = vec3_mul_vec(rec->normal, -1);
            return true;
        }
        i++;
    }*/
    return false;
}


    /*t_vec3 x = vec3_sub_vecs(ray->orig, cy->point);
    float var.d_dot = vec3_dot(ray->direc, cy->normal);
    float var.x_dot = vec3_dot(x, cy->normal);

    t_vec3 d_proj = vec3_mul_vec(cy->normal, var.d_dot);
    t_vec3 x_proj = vec3_mul_vec(cy->normal, var.x_dot);

    t_vec3 d_perp = vec3_sub_vecs(ray->direc, d_proj);
    t_vec3 x_perp = vec3_sub_vecs(x, x_proj);

    float a = vec3_dot(d_perp, d_perp);
    float b = 2.0 * vec3_dot(d_perp, x_perp);
    float c = vec3_dot(x_perp, x_perp) - (cy->radius * cy->radius);*/