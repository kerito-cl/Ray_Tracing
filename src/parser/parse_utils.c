/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:39:03 by mquero            #+#    #+#             */
/*   Updated: 2025/04/09 09:39:04 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	allocate_objects(char *file, t_info *info)
{
	int		fd;
	int		counter;
	char	*input;

	counter = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		throw_error(1);
	input = get_next_line(fd);
	if (input == NULL)
		throw_error(2);
	while (input != NULL)
	{
		counter++;
		free(input);
		input = get_next_line(fd);
	}
	free(input);
	if (counter > 200)
		free_arena_exit(info);
	info->lights = arena_alloc(info->arena, sizeof(t_obj *) * counter);
	info->obj = arena_alloc(info->arena, sizeof(t_obj) * counter);
	info->textures = arena_alloc(info->arena, sizeof(mlx_texture_t *)
			* counter);
	close(fd);
}
