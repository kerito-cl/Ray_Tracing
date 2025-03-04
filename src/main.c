/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:45:28 by mquero            #+#    #+#             */
/*   Updated: 2025/03/04 11:44:03 by mquero           ###   ########.fr       */
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

void	throw_rays(void *param)
{
	t_info *info;
	int col;
	int row;
	float x;
	float y;
	float aspect_ratio;

	info = (t_info *)param;
	while (row < HEIGHT)
	{
		col = 0;
		while (col < WIDTH)
		{
			x = (float)col / (WIDTH - 1);
			y = (float)row / (HEIGHT - 1);
			y = 1 - y;
			x = (x * 2) - 1;
			y = (y * 2) - 1;
			aspect_ratio = (float)WIDTH / HEIGHT;
			x = x * aspect_ratio;
			info->ray.direc.x = x;
			info->ray.direc.y = y;
			info->ray.direc.z = -1.5;
			vec_normalize(&(info->ray).direc);
			col++;
		}
		row++;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;
	int i = 0;
	if (argc != 2 || check_if_rt(argv[1]) == 0)
			throw_error(0);
	ft_bzero(&info, sizeof(t_info));
	info.arena = arena_init(10240);
	parse(argv[1], &info);
	//info.mlx =  mlx_init(WIDTH, HEIGHT, "KD MiniRT", true);
	//info.img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
 	//if (!info.img || (mlx_image_to_window(info.mlx, info.img, 0, 0) < 0))
		//return (0);
	//print_vec3(info.obj[8].point);
	/*while (i < info.obj_count)
	{
		print_vec3(info.obj[i].rgb);
		i++;
	}*/
	print_vec3(info.c.orient);
	printf("%f\n", info.c.fov);
	//mlx_loop_hook(info.mlx, &draw, &info);
	//mlx_loop(info.mlx);
	//free_all(&info);
	free_arena_exit(&info);
	return (0);	
}
