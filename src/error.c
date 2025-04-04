
#include "mini_rt.h"

void	free_all(t_info *info)
{
	int	i;

	i = 0;
	mlx_delete_image(info->mlx, info->img);
	mlx_terminate(info->mlx);
	arena_free(info->arena);
	exit(1);
}

void	throw_error(int flag)
{
	if (flag == 0)
	{
		printf(".rt file required as input\n");
		exit(1);
	}
	if (flag == 1)
	{
		printf("Your scene doesn't exist\n");
		exit(1);
	}
	if (flag == 2)
	{
		printf("Wrong file format\n");
		exit(1);
	}
	if (flag == 3)
	{
		printf("Malloc failed\n");
		exit(1);
	}
}

int	check_if_rt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.' && str[i + 1] == 'r' && str[i + 2] == 't' && str[i
			+ 3] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void	free_arena_exit(t_info *info)
{
	arena_free(info->arena);
	exit(1);
}

void	exit_free_parser(t_info *info, char **split, int n)
{
	int i = 0;

	while (i < info->texture_count)
		mlx_delete_texture(info->textures[i++]);
	freesplit(split);
	arena_free(info->arena);
	throw_error(n);
}