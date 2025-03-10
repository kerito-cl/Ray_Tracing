
#include "MLX42/MLX42.h"
#include "mini_rt.h"

void	print_vec3(t_vec3 vec3)
{
	printf("x : %f\n", vec3.x);
	printf("y : %f\n", vec3.y);
	printf("z : %f\n", vec3.z);
}


bool					light_hit(t_obj *obj, t_ray *ray, t_interval interval,
							t_hit_record *rec)
							{
								return true;
							}

bool					light_scatter(t_ray *r_in,
							t_hit_record *rec, t_vec3 *attenuation,
							t_ray *scattered)
							{
								return true;
							}

// this function belongs to camera.
t_vec3	ray_color(t_info *info, t_ray *ray, int depth)
{
	float			nearest;
	t_hit_record	rec;
	t_ray scattered;

	nearest = INFINITY;
	if (world_hit(info, ray, &rec, &nearest))
	{
		//printf("%f\n", nearest);
	}
	return vec3_new(0, 0, 0);
}


/**
 // ray_color
 if (world_hit(ray))
 {
	if (material is dif)
		send_shadow_rays();
	else
		send_ref_rays();
 }
 else
 {
	return (sky_color);
 }

 // send_shadow_rays()
if (is there  obstacle)
 	return (shadow color);
return (colors);

 // is there a obstacle?
 while (light in lights)
 {
	new ray;
	if (world_hit(ray))
		continue;
	else
		return false;
 }
 return true;


// send_ref_rays
check the




 * 
 * 
 * 
 */

/*void assign_ray_coordinates(t_ray *ray, int row, int col)
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
}*/
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
	row = 0;
	
	while (row < HEIGHT)
	{
		col = 0;
		while (col < WIDTH)
		{
			//assign_ray_coordinates(&ray, row, col);
			// assign the ray. 
			color = ray_color(info, &ray,50);
			col++;
		}
		row++;
	}
}

void	handle_win_close_event(void *param)
{
	t_info	*info;

	info = (t_info *)param;
	free_arena_exit(info);
	return (0);
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
	printf("NUMBER OF OBJECTS %u\n", info.obj_count);
	//print_vec3(info.obj[4].rgb);
	//print_vec3(info.l[0].rgb);
	//throw_rays(&info);
	camera_start(info); // call this function to start.
	//ft_memset(info.img->pixels, 255, info.img->width * info.img->height * sizeof(int32_t));
	//mlx_image_to_window(info.mlx, info.img, 0 , 0);
	mlx_close_hook(info.mlx, handle_win_close_event, &info);
	mlx_loop(info.mlx);
	// free_all(&info);
	free_arena_exit(&info);
	return (0);
}
