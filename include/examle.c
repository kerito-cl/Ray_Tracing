typedef struct object
{
    t_vec3 point;
	t_vec3 rgb;
    float radius;
	t_vec3 norm;
    float height;
    float br;

    bool (*hit)(t_ray *r);
} t_object;

t_object sp_new(t_vec3 center, t_vec3 rgb, float radius)
{
    t_object *obj = malloc();
    obj->point = center;
    obj->rgb = rgb;
    obj->radius = radious;
    obj->hit = sp_hit;
    return obj;
}

bool sp_hit(t_ray *r, t_hit_record *rec)
{

    return true;
}



t_object pl_new()