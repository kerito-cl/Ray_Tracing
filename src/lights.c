#include "mini_rt.h"

t_color    handle_ambient_light(t_info *info ,t_color *light_color)
{
    t_color a_light;

    a_light = vec3_copy(info->a.rgb);
    a_light = vec3_mul_vec(a_light, info->a.ratio);
    return (a_light);
}

t_color    handle_diffuse_light(t_info *info ,t_color *light_color, t_hit_record *rec)
{
    t_color dif_color;
    t_vec3 to_light;
    float intensity;

    // REC.P NEEDS TO BE NORMALIZE BEFORE CALLING LIGHT FUNCTIONS 

    
    to_light = vec3_sub_vecs(info->l.point, rec->p); 
    vec_normalize(&to_light); // TRY TO PASS TO_LIGHT VECTOR OUTSIDE THIS FUNCTION;
    dif_color = vec3_copy(info->l.rgb);
    intensity = fmaxf(vec3_dot(rec->p, to_light), 0);
    dif_color = vec3_mul_vec(dif_color, intensity);
    return (dif_color);
}

t_color    handle_specular_light(t_info *info ,t_color *light_color, t_hit_record *rec, t_ray ray)
{
    t_color specular_color;
    t_vec3 to_light;
    t_vec3 normal_vec;
    float intensity;

    // REC.P NEEDS TO BE NORMALIZE BEFORE CALLING LIGHT FUNCTIONS 

    to_light = vec3_sub_vecs(info->l.point, rec->p); 
    vec_normalize(&to_light); // TRY TO PASS TO_LIGHT VECTOR OUTSIDE THIS FUNCTION;
    intensity = vec3_dot(to_light, rec->p);
    normal_vec = vec3_mul_vec(rec->p, 2.0 * intensity);

    to_light = vec3_sub_vecs(to_light, normal_vec);
    //MAYBE NORMALIZE TO_LIGHT VECTOR

    intensity = fmaxf(vec3_dot(ray.direc, to_light), 0);
    intensity = pow(intensity, 30); //SECOND PARAMATER CHANGES THE SPECULAR SPOT LIGHT INTENSITY
    specular_color = vec3_mul_vec(info->l.rgb, intensity);
    return (specular_color);
}
