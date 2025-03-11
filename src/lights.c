#include "mini_rt.h"

t_color    get_ambient_light(t_info *info)
{
    t_color a_light;

    a_light = vec3_copy(info->a.rgb);
    a_light = vec3_mul_vec(a_light, info->a.ratio);
    return (a_light);
}

t_color    handle_diffuse_light(t_info *info, t_ray *shadow_ray)
{
    t_color dif_color;
    float intensity;

    // REC.P NEEDS TO BE NORMALIZE BEFORE CALLING LIGHT FUNCTIONS 

    
    //to_light = vec3_sub_vecs(info->l.point, rec->p); 
    //vec_normalize(&to_light); // TRY TO PASS TO_LIGHT VECTOR OUTSIDE THIS FUNCTION;
    dif_color = info->l.rgb;
    //shadow_ray->orig.z = shadow_ray->orig.z * -1;
    intensity = fmaxf(vec3_dot(shadow_ray->orig, shadow_ray->direc), 0);
    /*intensity = vec3_dot(shadow_ray->orig, shadow_ray->direc);
    intensity = -1 * intensity;*/
    //printf("%f\n", intensity);
    //intensity = vec3_dot(shadow_ray->orig, shadow_ray->direc) * -1;
    //intensity = fmaxf(intensity , 0);
    dif_color = vec3_mul_vec(dif_color, intensity);
    return (dif_color);
}

t_color    handle_specular_light(t_info *info ,t_ray *shadow_ray, t_ray *cam_ray)
{
    t_color specular_color;
    t_vec3 to_light;
    t_vec3 normal_vec;
    float intensity;

    // REC.P NEEDS TO BE NORMALIZE BEFORE CALLING LIGHT FUNCTIONS 

    intensity = vec3_dot(shadow_ray->orig, shadow_ray->direc); // NOt sure yet about FMAXF

    normal_vec = vec3_mul_vec(shadow_ray->orig, 2.0 * intensity);

    to_light = vec3_sub_vecs(shadow_ray->direc, normal_vec);
    vec3_normalize(&to_light);
    //MAYBE NORMALIZE TO_LIGHT VECTOR

    //intensity = fmaxf(vec3_dot(cam_ray->direc, shadow_ray->direc), 0);
    intensity = fmaxf(vec3_dot(cam_ray->direc, to_light), 0);
    intensity = powf(intensity, 30); //SECOND PARAMATER CHANGES THE SPECULAR SPOT LIGHT INTENSITY
    specular_color = vec3_mul_vec(info->l.rgb, intensity);
    return (specular_color);

}

t_color get_shadow_light(t_info *info)
{
    return (vec3_mul_vecs(get_ambient_light(info), vec3_new(0, 0, 0)));
}

t_color get_light_color(t_info *info, t_ray *shadow_ray, t_ray *cam_ray)
{
    t_color res;

    res = get_ambient_light(info);
    res = vec3_add_vecs(res, handle_diffuse_light(info, shadow_ray));

    res = vec3_add_vecs(res, handle_specular_light(info, shadow_ray, cam_ray));
    return res;
}

