
#include "MLX42/MLX42.h"
#include "mini_rt.h"

void	print_vec3(t_vec3 vec3)
{
	printf("x : %f\n", vec3.x);
	printf("y : %f\n", vec3.y);
	printf("z : %f\n", vec3.z);
}

bool	pl_hit(t_obj *sphere, t_ray *ray, t_interval interval, t_hit_record *rec)
{
	return (true);
}
bool	cy_hit(t_obj *sphere, t_ray *ray, t_interval interval, t_hit_record *rec)
{
	return (true);
}





bool world_hit(t_info *info, t_ray *ray, t_hit_record *rec, float *nearest)
{
	t_interval interval;
	int	i;
	float	t;

	i = 0;
	while (i < info->obj_count)
	{
		if (info->obj[i].hit(&info->obj[i], ray, interval, rec))
		{
			if (rec->t < *nearest)
				*nearest = rec->t;
		}
		i++;
	}
	if (*nearest == INFINITY)
	{
		return (false);
	}
	return (true);
}


// this function belongs to camera.
t_vec3	ray_color(t_info *info, t_ray *ray, int depth)
{
	float			nearest;
	t_hit_record	rec;
	t_ray scattered;

	nearest = INFINITY;
	if (world_hit(info, ray, &rec, &nearest))
	// we just get the nearest object here.
	// we don't care about the color.
	{
		printf("%f\n", nearest);
		//printf("%f\n", nearest);
		// we handle the color here.
		/*if (rec.material->scatter(rec.material, &ray, &rec, &scattered))
		{
			// we just send shadow ray.
			//if (rec.material->ref_idx == 0)
				//return (scattered.direc);
			// we need to handle the reflection or refraction.
			return (ray_color(info, scattered, depth - 1));
		}
		return ; // black;*/
	}
}

void assign_ray_coordinates(t_ray *ray, int row, int col)
{
	float x;
	float y;
	float aspect_ratio;

	x = (float)col / (WIDTH - 1);
	y = (float)row / (HEIGHT - 1);
	y = 1 - y;
	x = (x * 2) - 1;
	y = (y * 2) - 1;
	aspect_ratio = (float)WIDTH / HEIGHT;
	x = x * aspect_ratio;
	ray->direc.x = x;
	ray->direc.y = y;
	ray->direc.z = -1.0;
	vec_normalize(&ray->direc);
}
// this function belongs to camera.
void	throw_rays(void *param)
{
	t_info	*info;
	t_ray ray;
	t_color color;
	int		col;
	int		row;
	float	x;
	float	y;
	float	aspect_ratio;

	info = (t_info *)param;
	ray.orig = vec3_copy(info->c.point);
	while (row < HEIGHT)
	{
		col = 0;
		while (col < WIDTH)
		{
			assign_ray_coordinates(&ray, row, col);
			// assign the ray. 
			//info->screen[col][row] = ray_color(info, ray, 50);
			color = ray_color(info, &ray,50);
			col++;
		}
		row++;
	}
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
	//info.mlx =  mlx_init(WIDTH, HEIGHT, "KD MiniRT", true);
	//info.img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
	 //if (!info.img || (mlx_image_to_window(info.mlx, info.img, 0, 0) < 0))
	// return (0);
	// print_vec3(info.obj[8].point);

	// print_vec3(info.c.orient);
	printf("%u\n", info.obj_count);
	throw_rays(&info);

	//ft_memset(info.img->pixels, 255, info.img->width * info.img->height * sizeof(int32_t));
	//mlx_image_to_window(info.mlx, info.img, 0 , 0);
	// mlx_loop_hook(info.mlx, &draw, &info);
	//mlx_loop(info.mlx);
	// free_all(&info);
	free_arena_exit(&info);
	return (0);
}
