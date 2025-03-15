#include "mini_rt.h"

void	print_position(t_info *info);
void	handle_transition_event(t_info *info, keys_t key);

void	handle_win_close_event(void *param)
{
	t_info	*info;

	info = (t_info *)param;
	free_arena_exit(info);
}

void	handle_rotation_lr(t_info *info, keys_t key)
{
	float cos;
	float sin;
	t_vec3 orient;

	cos = cosf(ROTATE_STEP);
	sin = sinf(ROTATE_STEP);
	orient = info->c.orient;
	if (key == MLX_KEY_A)
	{
		orient.x = info->camera.orient.x * cos - info->camera.orient.z * sin;
		orient.z = info->camera.orient.x * sin + info->camera.orient.z * cos;
	}
	else if (key == MLX_KEY_D)
	{
		orient.x = info->camera.orient.x * cos + info->camera.orient.z * sin;
		orient.z = info->camera.orient.z * cos - info->camera.orient.x * sin;		
	}
	info->camera.orient = vec3_unit(orient);
	camera_render(info);
}

void	handle_rotation_ud(t_info *info, keys_t key)
{
	float cos;
	float sin;
	t_vec3 orient;

	cos = cosf(ROTATE_STEP);
	sin = sinf(ROTATE_STEP);
	orient = info->c.orient;
	if (key == MLX_KEY_W)
	{
		orient.y = info->camera.orient.y * cos - info->camera.orient.z * sin;
		orient.z = info->camera.orient.y * sin + info->camera.orient.z * cos;
	}
	else if (key == MLX_KEY_S)
	{
		orient.y = info->camera.orient.y * cos + info->camera.orient.z * sin;
		orient.z = info->camera.orient.z * cos - info->camera.orient.y * sin;
	}
	info->camera.orient = vec3_unit(orient);
	camera_render(info);
}

void	handle_key_press_event(mlx_key_data_t keydata, void *param)
{
	t_info	*info;
	int		x;
	int		y;

	info = (t_info *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		free_arena_exit(info);
	if (keydata.key == MLX_KEY_D)
		print_position(info);
	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT 
		|| keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
		handle_transition_event(info, keydata.key);
	if (keydata.key == MLX_KEY_A|| keydata.key == MLX_KEY_D)
		handle_rotation_lr(info, keydata.key);
	if (keydata.key == MLX_KEY_W|| keydata.key == MLX_KEY_S)
		handle_rotation_ud(info, keydata.key);
}

void 	handle_screen_resize(int32_t width, int32_t height, void* param)
{
	t_info	*info;

	info = (t_info *)param;
	camera_resize_screen(info, width, height);
}
