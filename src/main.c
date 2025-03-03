/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:45:28 by mquero            #+#    #+#             */
/*   Updated: 2025/03/03 12:28:59 by mquero           ###   ########.fr       */
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

bool sp_hit(t_ray *r, t_hit_record *rec){return true;}
bool pl_hit(t_ray *r, t_hit_record *rec){return true;}
bool cy_hit(t_ray *r, t_hit_record *rec){return true;}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 2 || check_if_rt(argv[1]) == 0)
			throw_error(0);
	ft_bzero(&info, sizeof(t_info));
	info.arena = arena_init(10240);
	parse(argv[1], &info);
	info.mlx =  mlx_init(WIDTH, HEIGHT, "KD MiniRT", true);
	info.img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
 	if (!info.img || (mlx_image_to_window(info.mlx, info.img, 0, 0) < 0))
		return (0);
	//print_vec3(info.obj[8].point);
	printf("%d\n",info.obj[0].type_material);
	printf("%d\n",info.obj[1].type_material);
	printf("%d\n",info.obj[2].type_material);
	printf("%d\n",info.obj[3].type_material);
	printf("%d\n",info.obj[4].type_material);
	printf("%d\n",info.obj[5].type_material);
	printf("%d\n",info.obj[6].type_material);
	printf("%d\n",info.obj[7].type_material);
	printf("%d\n",info.obj[8].type_material);
	
	//mlx_loop_hook(info.mlx, &draw, &info);
	//mlx_loop(info.mlx);
	free_all(&info);
	return (0);	
}
