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

    dif_color = info->l.rgb;
    intensity = fmaxf(vec3_dot(shadow_ray->orig, shadow_ray->direc), 0);
    dif_color = vec3_mul_vec(dif_color, intensity);
    return (dif_color);
}

t_color    handle_specular_light(t_info *info ,t_ray *shadow_ray, t_ray *cam_ray)
{
    t_color specular_color;
    t_vec3 to_light;
    t_vec3 normal_vec;
    float intensity;

    intensity = vec3_dot(shadow_ray->orig, shadow_ray->direc); // NOt sure yet about FMAXF
    normal_vec = vec3_mul_vec(shadow_ray->orig, 2.0 * intensity);
    to_light = vec3_sub_vecs(shadow_ray->direc, normal_vec);
    vec3_normalize(&to_light);

    intensity = fmaxf(vec3_dot(cam_ray->direc, to_light), 0);
    intensity = powf(intensity, 30); //SECOND PARAMATER CHANGES THE SPECULAR SPOT LIGHT INTENSITY
    specular_color = vec3_mul_vec(info->l.rgb, intensity);
    return (specular_color);

}

t_color get_light_color(t_info *info, t_ray *shadow_ray, t_ray *cam_ray)
{
    t_color res;

    res = get_ambient_light(info);
    res = vec3_add_vecs(res, handle_diffuse_light(info, shadow_ray));
    res = vec3_add_vecs(res, handle_specular_light(info, shadow_ray, cam_ray));
    return res;
}

