
#include "mini_rt.h"

void		new_vec3_for_parsing(t_vec3 *vec3, char **cvec, bool *isvalid,
				bool if_rgb);
                
static void assign_typematerial_info(t_info *info, char *material, int i)
{
    if (ft_strncmp(material, "M\n", ft_strlen(material)) == 0)
        info->obj[i].type_material = METAL;
    else if (ft_strncmp(material, "G\n", ft_strlen(material)) == 0)
        info->obj[i].type_material = GLASS;
    else if (ft_strncmp(material, "D\n", ft_strlen(material)) == 0)
        info->obj[i].type_material = DIFFUSE;
}

void create_plane_info(t_info *info, char **split, int i, bool *isvalid)
{
    char  **vec;
    
    vec = ft_split(split[1], ',');
    if (!vec)
        exit_free_parser(info, split, 2);
    new_vec3_for_parsing(&(info->obj[i]).point, vec, isvalid, false);
    vec = ft_split(split[2], ',');
    if (!vec)
        exit_free_parser(info, split, 2);
    new_vec3_for_parsing(&(info->obj[i]).normal, vec, isvalid, false);
    vec = ft_split(split[3], ',');
    if (!vec)
        exit_free_parser(info, split, 2);
    new_vec3_for_parsing(&(info->obj[i]).rgb, vec, isvalid, true);
    assign_typematerial_info(info, split[4], i);
    info->obj[i].hit = pl_hit;
}

void create_sphere_info(t_info *info, char **split, int i, bool *isvalid)
{
    char  **vec;
    char    *ptr;

    info->obj[i].radius = ft_strtof(split[2], &ptr) * 0.5;
    if (ptr[0] != 0)
        exit_free_parser(info, split, 2);
    vec = ft_split(split[1], ',');
    if (!vec)
        exit_free_parser(info, split, 3);
    new_vec3_for_parsing(&(info->obj[i]).point, vec,isvalid, false);
    vec = ft_split(split[3], ',');
    if (!vec)
        exit_free_parser(info, split, 3);
    new_vec3_for_parsing(&(info->obj[i]).rgb, vec, isvalid, true);
    assign_typematerial_info(info, split[4], i);
    info->obj[i].hit = sp_hit;
}

void create_cylinder_info(t_info *info, char **split, int i, bool *isvalid)
{
    char  **vec;
    char    *ptr;

    info->obj[i].radius = ft_strtof(split[3], &ptr) * 0.5;
    if (ptr[0] != 0)
        exit_free_parser(info, split, 2);
    info->obj[i].height = ft_strtof(split[4], &ptr);
    if (ptr[0] != 0)
        exit_free_parser(info, split, 2);
    vec = ft_split(split[1], ',');
    if (!vec)
        exit_free_parser(info, split, 3);
    new_vec3_for_parsing(&(info->obj[i]).point, vec, isvalid ,false);
    vec = ft_split(split[2], ',');
    if (!vec)
        exit_free_parser(info, split, 3);
    new_vec3_for_parsing(&(info->obj[i]).normal, vec, isvalid ,false);
    vec = ft_split(split[5], ',');
    if (!vec)
        exit_free_parser(info, split, 3);
    new_vec3_for_parsing(&(info->obj[i]).rgb, vec, isvalid,true);
    assign_typematerial_info(info, split[6], i);
    info->obj[i].hit = cy_hit;
    //info->obj[i].material.scatter = cy_scatter;
}

void create_object_info(t_info *info, char **split)
{
    bool    isvalid;
    static  int i = 0;

    isvalid = true;
    if (ft_strncmp(split[0], "pl", ft_strlen(split[0])) == 0)
        create_plane_info(info, split, i, &isvalid);
    else if (ft_strncmp(split[0], "sp", ft_strlen(split[0])) == 0)
        create_sphere_info(info, split, i, &isvalid);
    else if (ft_strncmp(split[0], "cy", ft_strlen(split[0])) == 0)
        create_cylinder_info(info, split, i, &isvalid);
    if (!isvalid)
        exit_free_parser(info, split, 2);
    i++;
    info->obj_count = i;
}

