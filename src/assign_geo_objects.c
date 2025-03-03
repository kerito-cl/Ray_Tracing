/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_geo_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:53:16 by mquero            #+#    #+#             */
/*   Updated: 2025/03/03 13:19:46 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool sp_hit(t_ray *r, t_hit_record *rec);
bool pl_hit(t_ray *r, t_hit_record *rec);
bool cy_hit(t_ray *r, t_hit_record *rec);

static void assign_typematerial_info(t_info *info, char *material, int i)
{
    printf("%zu\n", ft_strlen(material));
    if (ft_strncmp(material, "M\n", ft_strlen(material)) == 0)
        info->obj[i].type_material = METAL;
    else if (ft_strncmp(material, "G\n", ft_strlen(material)) == 0)
        info->obj[i].type_material = GLASS;
    else if (ft_strncmp(material, "D\n", ft_strlen(material)) == 0)
        info->obj[i].type_material = DIFFUSE;
}

void create_plane_info(t_info *info, char **split, int i)
{
    char  **vec;
    static  int j = 0;
    
    vec = ft_split(split[1], ',');
    if (!vec)
        free_arena_exit(info);
    new_vec3(&(info->obj[i]).point, vec, false);
    vec = ft_split(split[2], ',');
    if (!vec)
        free_arena_exit(info);
    new_vec3(&(info->obj[i]).norm, vec, false);
    vec = ft_split(split[3], ',');
    if (!vec)
        free_arena_exit(info);
    new_vec3(&(info->obj[i]).rgb, vec, true);
    assign_typematerial_info(info, split[4], i);
    info->obj[i].hit = pl_hit;
    j++;
    info->pl_count = j;
}

void create_sphere_info(t_info *info, char **split, int i)
{
    char  **vec;
    static  int j = 0;

    info->obj[i].radius = strtof(split[2], NULL) * 0.5;
    vec = ft_split(split[1], ',');
    if (!vec)
        free_arena_exit(info);
    new_vec3(&(info->obj[i]).point, vec, false);
    vec = ft_split(split[3], ',');
    if (!vec)
        free_arena_exit(info);
    new_vec3(&(info->obj[i]).rgb, vec, true);
    assign_typematerial_info(info, split[4], i);
    info->obj[i].hit = sp_hit;
    j++;
    info->sp_count = j;
}

void create_cylinder_info(t_info *info, char **split, int i)
{
    char  **vec;
    static  int j = 0;

    info->obj[i].radius = strtof(split[3], NULL) * 0.5;
    info->obj[i].height = strtof(split[4], NULL);
    vec = ft_split(split[1], ',');
    if (!vec)
        free_arena_exit(info);
    new_vec3(&(info->obj[i]).point, vec, false);
    vec = ft_split(split[2], ',');
    if (!vec)
        free_arena_exit(info);
    new_vec3(&(info->obj[i]).norm, vec, false);
    vec = ft_split(split[5], ',');
    if (!vec)
        free_arena_exit(info);
    new_vec3(&(info->obj[i]).rgb, vec, true);
    assign_typematerial_info(info, split[6], i);
    info->obj[i].hit = cy_hit;
    j++;
    info->cy_count = j;
}
void create_object_info(t_info *info, char **split)
{
    static  int i = 0;


    if (ft_strncmp(split[0], "pl", ft_strlen(split[0])) == 0)
        create_plane_info(info, split, i);
    else if (ft_strncmp(split[0], "sp", ft_strlen(split[0])) == 0)
        create_sphere_info(info, split, i);
    else if (ft_strncmp(split[0], "cy", ft_strlen(split[0])) == 0)
        create_cylinder_info(info, split, i);
    i++;
    info->obj_count = i;
}

