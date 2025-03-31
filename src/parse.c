#include "constants.h"
#include "mini_rt.h"

static void	assign_camera_info(t_info *info, char **split, bool *isvalid)
{
	char	**vec;
	char	*ptr;

	info->c.hov = ft_strtof(split[3], &ptr);
	if (ptr[0] != '\0' && ptr[0] != '\n')
		exit_free_parser(info, split, 2);
	vec = ft_split(split[1], ',');
	if (!vec)
		free_arena_exit(info);
	new_vec3_for_parsing(&(info->c).point, vec, isvalid, false);
	vec = ft_split(split[2], ',');
	if (!vec)
		free_arena_exit(info);
	new_vec3_for_parsing(&(info->c).orient, vec, isvalid, false);
	if (split[4] != NULL)
		exit_free_parser(info, split, 2);
}

static void	assign_ambient_info(t_info *info, char **split, bool *isvalid)
{
	char	**rgb;
	char	*ptr;

	info->a.ratio = ft_strtof(split[1], &ptr);
	if (ptr[0] != 0)
		exit_free_parser(info, split, 2);
	rgb = ft_split(split[2], ',');
	if (!rgb)
		free_arena_exit(info);
	new_vec3_for_parsing(&(info->a).rgb, rgb, isvalid, true);
	if (split[3] != NULL)
		exit_free_parser(info, split, 2);
}

void	create_light_info(t_info *info, char **split, int i, bool *isvalid)
{
	static int	j = 0;
	char		**vec;
	char		*ptr;

	info->obj[i].radius = LIGHT_RADIUS;
	info->obj[i].br_ratio = ft_strtof(split[2], &ptr);
	if (ptr[0] != 0)
		exit_free_parser(info, split, 2);
	vec = ft_split(split[3], ',');
	if (!vec)
		free_arena_exit(info);
	new_vec3_for_parsing(&(info->obj[i]).rgb, vec, isvalid, true);
	vec = ft_split(split[1], ',');
	if (!vec)
		free_arena_exit(info);
	new_vec3_for_parsing(&(info->obj[i]).point, vec, isvalid, false);
	info->obj[i].hit = sp_hit;
	assign_typematerial_info(info, split[0], i, split);
	info->obj[i].material.texture_get_color = texutre_constant_color;
	info->lights[j] = &info->obj[i];
	j++;
	info->light_count = j;
}

static void	assign_all(t_info *info, char **split)
{
	bool	isvalid;

	isvalid = true;
	if (ft_strncmp(split[0], "\n", ft_strlen(split[0])) == 0)
		return ;
	else if (ft_strncmp(split[0], "A", ft_strlen(split[0])) == 0)
		assign_ambient_info(info, split, &isvalid);
	else if (ft_strncmp(split[0], "C", ft_strlen(split[0])) == 0)
		assign_camera_info(info, split, &isvalid);
	else if (ft_strncmp(split[0], "L", ft_strlen(split[0])) == 0)
		create_object_info(info, split);
	else if (ft_strncmp(split[0], "pl", ft_strlen(split[0])) == 0)
		create_object_info(info, split);
	else if (ft_strncmp(split[0], "sp", ft_strlen(split[0])) == 0)
		create_object_info(info, split);
	else if (ft_strncmp(split[0], "cy", ft_strlen(split[0])) == 0)
		create_object_info(info, split);
	else if (ft_strncmp(split[0], "cn", ft_strlen(split[0])) == 0)
		create_object_info(info, split);
	else
		exit_free_parser(info, split, 2);
	if (!isvalid)
		exit_free_parser(info, split, 2);
}

void	parse(char *file, t_info *info)
{
	int		fd;
	char	*input;
	char	**split;

	info->lights = arena_alloc(info->arena, sizeof(t_obj *) * 10);
	info->obj = arena_alloc(info->arena, sizeof(t_obj) * 100);
	info->textures = arena_alloc(info->arena, sizeof(mlx_texture_t *) * 100);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		throw_error(1);
	input = get_next_line(fd);
	if (input == NULL)
		throw_error(2);
	while (input != NULL)
	{
		split = ft_split(input, ' ');
		free(input);
		if (!split)
			free_arena_exit(info);
		assign_all(info, split);
		freesplit(split);
		input = get_next_line(fd);
	}
	close(fd);
}

// info->obj = ft_memmove(info->l + info->light_count, info->obj,
//		sizeof(t_obj));
//* info->pl_count);
// info->cy = ft_memmove(info->pl + info->pl_count, info->cy, sizeof(t_cy)
//* info->cy_count);