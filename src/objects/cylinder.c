
#include "mini_rt.h"

static float quadratic(float a, float b, float c)
{
    float discriminant;
    float t0;
    float t1;

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

bool	cy_hit(t_obj *cy, t_ray *ray, t_interval *interval, t_hit_record *rec)
{
    t_vec3 l;
    float a;
    float b;
    float c;
    float heght_radius;

    heght_radius = cy->height * 0.5; 
    l = vec3_copy(ray->orig);
    l = vec3_sub_vecs(l, cy->point);
    a = (ray->direc.x * ray->direc.x) + (ray->direc.z * ray->direc.z);
    b = 2 * ((ray->direc.x * l.x) + (ray->direc.z * l.z));
    c = (l.x * l.x) + (l.z * l.z)- (cy->radius * cy->radius);
    rec->t = quadratic(a, b, c);
    rec->p = ray_at(ray, rec->t);
    if (rec->t > 0.0 && rec->p.y > (cy->point.y -heght_radius) && rec->p.y < (cy->point.y + heght_radius))
    {
	    rec->material = &cy->material;
        rec->normal = vec3_sub_vecs(rec->p, cy->point);
        rec->normal.y = 0;
        a = vec3_dot(rec->normal, ray->direc);
        if (a > 0)
            rec->normal =  vec3_mul_vec(rec->normal, -1);
        return (true);
    }
    return (false);
}  
/*bool	cy_hit(t_obj *cy, t_ray *ray, t_interval interval, t_hit_record *rec)
{
    

}*/
