
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
	info.arena = arena_init(10240);
	parse(argv[1], &info);
	printf("NUMBER OF OBJECTS %u\n", info.obj_count);
	camera_start(&info);
	mlx_close_hook(info.mlx, handle_win_close_event, &info);
	mlx_key_hook(info.mlx, handle_key_press_event, &info);
	mlx_resize_hook(info.mlx, handle_screen_resize, &info);
	mlx_loop(info.mlx);
	free_arena_exit(&info);
	return (0);
}
