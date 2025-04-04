#include "mini_rt.h"

void	assign_texture_info(t_info *info, char *texture, int i, char **split);

void	create_box_info(t_info *info, char **split, int i, bool *isvalid)
{
	char	**vec;
	char	*ptr;

	vec = ft_split(split[1], ',');
	if (!vec)
		exit_free_parser(info, split, 3);
	new_vec3_for_parsing(&(info->obj[i]).min, vec, isvalid, false);
	vec = ft_split(split[2], ',');
	if (!vec)
		exit_free_parser(info, split, 3);
	new_vec3_for_parsing(&(info->obj[i]).max, vec, isvalid, false);
	vec = ft_split(split[3], ',');
	if (!vec)
		exit_free_parser(info, split, 3);
	new_vec3_for_parsing(&(info->obj[i]).rgb, vec, isvalid, true);
	assign_typematerial_info(info, split[4], i, split);
	if (split[4] == NULL)
		info->obj[i].material.texture_get_color = texutre_constant_color;
	else
		assign_texture_info(info, split[5], i, split);
	info->obj[i].hit = box_hit;
}
