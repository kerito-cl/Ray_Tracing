#include "constants.h"
#include "mini_rt.h"

static void	assign_camera_info(t_info *info, char **split,bool *isvalid)
{
	char	**vec;

	info->c.fov = ft_strtof(split[3], NULL);
	vec = ft_split(split[1], ',');
	if (!vec)
		free_arena_exit(info);
	new_vec3_for_parsing(&(info->c).point, vec, isvalid, false);
	vec = ft_split(split[2], ',');
	if (!vec)
		free_arena_exit(info);
	new_vec3_for_parsing(&(info->c).orient, vec, isvalid, false);
	info->c.look_at = vec3_new(0, 0, -1);
	info->c.image_height = IMG_HEIGHT;
	info->c.image_width = IMG_WIDTH;
}

static void	assign_ambient_info(t_info *info, char **split, bool *isvalid)
{
	char	**rgb;

	info->a.ratio = ft_strtof(split[1], NULL);
	rgb = ft_split(split[2], ',');
	if (!rgb)
		free_arena_exit(info);
	new_vec3_for_parsing(&(info->a).rgb, rgb, isvalid, true);
}

void	assign_light_info(t_info *info, char **split,bool *isvalid)
{
	static int i = 0;
	char	**vec;

	info->l[i].br_ratio = ft_strtof(split[2], NULL);
	vec = ft_split(split[3], ',');
	if (!vec)
		free_arena_exit(info);
	new_vec3_for_parsing(&(info->l[i]).rgb, vec, isvalid, true);
	vec = ft_split(split[1], ',');
	if (!vec)
		free_arena_exit(info);
	new_vec3_for_parsing(&(info->l[i]).point, vec, isvalid, false);
	i++;
	info->light_count = i;
	//info->obj[i].hit = light_hit;
	//info->obj[i].material.albedo = info->l.rgb;
	//info->obj[i].material.scatter = light_scatter;
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
		assign_light_info(info, split, &isvalid);
	else if (ft_strncmp(split[0], "pl", ft_strlen(split[0])) == 0)
		create_object_info(info, split);
	else if (ft_strncmp(split[0], "sp", ft_strlen(split[0])) == 0)
		create_object_info(info, split);
	else if (ft_strncmp(split[0], "cy", ft_strlen(split[0])) == 0)
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

	info->l = arena_alloc(info->arena, sizeof(t_light) * 10);
	info->obj = arena_alloc(info->arena, sizeof(t_obj) * 100);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		throw_error(1);
	input = get_next_line(fd);
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
	//info->obj = ft_memmove(info->l + info->light_count, info->obj, sizeof(t_obj));
			//* info->pl_count);
	// info->cy = ft_memmove(info->pl + info->pl_count, info->cy, sizeof(t_cy)
	//* info->cy_count);
}
