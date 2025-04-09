/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:47:51 by mquero            #+#    #+#             */
/*   Updated: 2025/04/09 09:48:28 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "mini_rt.h"

void	print_vec3(t_vec3 vec3)
{
	printf("x : %f\n", vec3.x);
	printf("y : %f\n", vec3.y);
	printf("z : %f\n", vec3.z);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		i;

	i = 0;
	if (argc != 2 || check_if_rt(argv[1]) == 0)
		throw_error(0);
	ft_bzero(&info, sizeof(t_info));
	info.arena = arena_init(MAX_MEMORY);
	if (!info.arena)
		throw_error(0);
	parse(argv[1], &info);
	camera_start(&info);
	mlx_set_window_limit(info.mlx, MIN_WIDTH, MIN_HEIGHT, MAX_WIDTH,
		MAX_HEIGHT);
	mlx_close_hook(info.mlx, handle_win_close_event, &info);
	mlx_key_hook(info.mlx, handle_key_press_event, &info);
	mlx_resize_hook(info.mlx, handle_screen_resize, &info);
	mlx_loop(info.mlx);
	free_all(&info);
	return (0);
}
