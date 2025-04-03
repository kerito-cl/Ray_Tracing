#include "mini_rt.h"

void	create_plane_info(t_info *info, char **split, int i, bool *isvalid);
void	create_cylinder_info(t_info *info, char **split, int i, bool *isvalid);
void	create_sphere_info(t_info *info, char **split, int i, bool *isvalid);
void	create_cone_info(t_info *info, char **split, int i, bool *isvalid);
void	create_box_info(t_info *info, char **split, int i, bool *isvalid);

void	assign_typematerial_info(t_info *info, char *material, int i,
		char **split)
{
	if (material == NULL || ft_strncmp(material, "D", 1) == 0
		|| material[0] == '\n')
	{
		info->obj[i].material.albedo = info->obj[i].rgb;
		info->obj[i].type_material = DIFFUSE;
		info->obj[i].material.scatter = lambertian_scatter;
	}
	else if (ft_strncmp(material, "M", 1) == 0)
		assign_metal(info, material, i, split);
	else if (ft_strncmp(material, "G", 1) == 0)
		assign_glass(info, material, i, split);
	else if (ft_strncmp(material, "A", 1) == 0)
		assign_air(info, material, i, split);
	else if (ft_strncmp(material, "W", 1) == 0)
		assign_water(info, material, i, split);
	else if (ft_strncmp(material, "L", 1) == 0)
		assign_lights(info, material, i, split);
	else
		exit_free_parser(info, split, 2);
}

void	set_texture(t_info *info, char *filename, int i, char **split)
{
	int				fd;
	int				len;
	mlx_texture_t	*texture;
	static int		k = 0;

	len = ft_strlen(filename);
	if (len < 5)
		exit_free_parser(info, split, 2);
	filename[--len] = '\0';
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_free_parser(info, split, 2);
	if (ft_strncmp(".png", filename + len - 4, 4) == 0)
		texture = mlx_load_png(filename);
	else
	{
		close(fd);
		exit_free_parser(info, split, 2);
	}
	if (!texture)
		exit_free_parser(info, split, 2);
	info->textures[k] = texture;
	++(info->texture_count);
	info->obj[i].material.texture_img_idx = k;
	k++;
}

void	assign_texture_info(t_info *info, char *texture, int i, char **split)
{
	if (!texture || !*texture || info->obj[i].type_material != DIFFUSE
		|| texture[0] == '\n')
		info->obj[i].material.texture_get_color = texutre_constant_color;
	else if (ft_strncmp(texture, "C\n", ft_strlen(texture)) == 0)
	{
		info->obj[i].material.albedo2 = vec3_sub_vecs(vec3_new(1, 1, 1),
				info->obj[i].rgb);
		vec3_print(info->obj[i].material.albedo2);
		info->obj[i].material.scale = CHECK_SCALE;
		info->obj[i].material.texture_get_color = texture_checker_color;
	}
	else if (ft_strncmp(texture, "F:", 2) == 0)
	{
		info->obj[i].material.texture_get_color = texture_img_color;
		set_texture(info, texture + 2, i, split);
	}
	else
		exit_free_parser(info, split, 2);
}

void	create_object_info(t_info *info, char **split)
{
	bool isvalid;
	static int i = 0;

	isvalid = true;
	if (ft_strncmp(split[0], "pl", ft_strlen(split[0])) == 0)
		create_plane_info(info, split, i, &isvalid);
	else if (ft_strncmp(split[0], "sp", ft_strlen(split[0])) == 0)
		create_sphere_info(info, split, i, &isvalid);
	else if (ft_strncmp(split[0], "cy", ft_strlen(split[0])) == 0)
		create_cylinder_info(info, split, i, &isvalid);
	else if (ft_strncmp(split[0], "cn", ft_strlen(split[0])) == 0)
		create_cone_info(info, split, i, &isvalid);
	else if (ft_strncmp(split[0], "bx", ft_strlen(split[0])) == 0)
		create_box_info(info, split, i, &isvalid);
	else if (ft_strncmp(split[0], "L", ft_strlen(split[0])) == 0)
		create_light_info(info, split, i, &isvalid);
	if (!isvalid)
		exit_free_parser(info, split, 2);
	i++;
	info->obj_count = i;
}
