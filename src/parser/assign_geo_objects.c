
#include "mini_rt.h"

bool		sp_hit(t_obj *sphere, t_ray *ray, t_interval *interval,
				t_hit_record *rec);

void		new_vec3_for_parsing(t_vec3 *vec3, char **cvec, bool *isvalid,
				bool if_rgb);
void		assign_texture_info(t_info *info, char *texture, int i,
				char **split);

void	create_plane_info(t_info *info, char **split, int i, bool *isvalid)
{
	char	**vec;

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
	assign_typematerial_info(info, split[4], i, split);
	if (split[4] == NULL)
		info->obj[i].material.texture_get_color = texutre_constant_color;
	else
		assign_texture_info(info, split[5], i, split);
	info->obj[i].hit = pl_hit;
}

void	create_sphere_info(t_info *info, char **split, int i, bool *isvalid)
{
	char	**vec;
	char	*ptr;

	info->obj[i].radius = ft_strtof(split[2], &ptr) * 0.5;
	if (ptr[0] != 0)
		exit_free_parser(info, split, 2);
	vec = ft_split(split[1], ',');
	if (!vec)
		exit_free_parser(info, split, 3);
	new_vec3_for_parsing(&(info->obj[i]).point, vec, isvalid, false);
	vec = ft_split(split[3], ',');
	if (!vec)
		exit_free_parser(info, split, 3);
	new_vec3_for_parsing(&(info->obj[i]).rgb, vec, isvalid, true);
	assign_typematerial_info(info, split[4], i, split);
	if (split[4] == NULL)
		info->obj[i].material.texture_get_color = texutre_constant_color;
	else
		assign_texture_info(info, split[5], i, split);
	info->obj[i].hit = sp_hit;
}

static void	create_cy_or_cn_info(t_info *info, char **split, int i,
		bool *isvalid)
{
	char	**vec;
	char	*ptr;

	info->obj[i].height = ft_strtof(split[4], &ptr);
	if (ptr[0] != 0)
		exit_free_parser(info, split, 2);
	vec = ft_split(split[1], ',');
	if (!vec)
		exit_free_parser(info, split, 3);
	new_vec3_for_parsing(&(info->obj[i]).point, vec, isvalid, false);
	vec = ft_split(split[2], ',');
	if (!vec)
		exit_free_parser(info, split, 3);
	new_vec3_for_parsing(&(info->obj[i]).normal, vec, isvalid, false);
	vec = ft_split(split[5], ',');
	if (!vec)
		exit_free_parser(info, split, 3);
	new_vec3_for_parsing(&(info->obj[i]).rgb, vec, isvalid, true);
	assign_typematerial_info(info, split[6], i, split);
	if (split[6] == NULL)
		info->obj[i].material.texture_get_color = texutre_constant_color;
	else
		assign_texture_info(info, split[7], i, split);
}

void	create_cylinder_info(t_info *info, char **split, int i, bool *isvalid)
{
	char	*ptr;

	info->obj[i].radius = ft_strtof(split[3], &ptr) * 0.5;
	if (ptr[0] != 0)
		exit_free_parser(info, split, 2);
	create_cy_or_cn_info(info, split, i, isvalid);
	info->obj[i].hit = cy_hit;
}

void	create_cone_info(t_info *info, char **split, int i, bool *isvalid)
{
	char	*ptr;

	info->obj[i].radius = ft_strtof(split[3], &ptr) * 0.5;
	if (ptr[0] != 0)
		exit_free_parser(info, split, 2);
	create_cy_or_cn_info(info, split, i, isvalid);
	info->obj[i].hit = cn_hit;
}
