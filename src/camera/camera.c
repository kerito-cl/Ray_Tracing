#include "constants.h"
#include "mini_rt.h"

void camera_init(t_cam *c);
t_ray camera_get_ray(t_cam *c, int i, int j);
t_color camera_ray_color(t_info *info, t_ray ray, t_obj **world, int depth);

unsigned int get_color(t_vec3 vec1, t_vec3 vec2, float t)
{
	float	r;
	float	g;
	float	b;
	if (t > 1)
		t = 1;
	if (t < 0)
		t = 0;
	r = vec1.x + (vec2.x - vec1.x) * t ;
	//r = vec1.x;
	r *= 255.0;
	if (r > 255)
		r = 255;
	g = vec1.y + (vec2.y - vec1.y) * t;
	//g = vec1.y;
	g *= 255.0;
	if (g > 255)
		g = 255;
	b = vec1.z + (vec2.z - vec1.z) * t;
	//b = vec1.z;
	b *= 255.0;
	if (b > 255)
		b = 255.0;
	return (((size_t)r << 24) + ((size_t)g << 16) + ((size_t)b << 8) + 255);
}


void camera_render(void *param)
{
	int j;
	int i;
	int k;
	t_ray ray;
	t_color color;
	t_color fog;
	uint32_t packed_color;
	t_info *info;

	k = 0;
	info = (t_info *)param;
	fog.x = (float)178 / 255;
	fog.y = (float)178 / 255;
	fog.z = (float)178 / 255;
	camera_init(&info->c);
	j = 0;
	ray.orig = info->c.point;
	while (j < info->c.image_height)
	{
		i = 0;
		while (i < info->c.image_width)
		{
			ray = camera_get_ray(&info->c, i, j);

			color = camera_ray_color(info, ray, &info->obj, MAX_DEPTH);
			//packed_color = (255 << 24) | ((uint8_t)(color.z * 255) << 16) | ((uint8_t)(color.y * 255) << 8) | (uint8_t)(color.x * 255);
			//packed_color = ((size_t)color.x << 24) + ((size_t)color.y << 16) + ((size_t)color.z << 8) + 255;
			packed_color = get_color(color, fog, 0.004);
			//mlx_put_pixel(info->img, i, j, packed_color);
			info->img->pixels[k] = color.x * 255;
			k++;
			info->img->pixels[k] = color.y * 255;
			k++;
			info->img->pixels[k] = color.z * 255;
			k++;
			info->img->pixels[k] = 255;
			k++;
			++i;
		}
		++j;
	}
	mlx_image_to_window(info->mlx, info->img, 0, 0);
}

void camera_start(t_info *info)
{
	info->c.image_height = IMG_HEIGHT;
	info->c.image_width = IMG_WIDTH;
	info->mlx =  mlx_init(IMG_WIDTH, IMG_HEIGHT, "KD MiniRT", true);
	info->img = mlx_new_image(info->mlx, info->c.image_width, info->c.image_height);
	if (!info->img || mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
		free_all(info);
	camera_render(info);
	mlx_loop_hook(info->mlx, camera_render, info);
}

void camera_resize_screen(t_info *info, int image_width, int image_height)
{
	if (image_height < MAX_HEIGHT)
		info->c.image_height = image_height / 8 * 8;
	if (image_height < MAX_WIDTH)
		info->c.image_width = image_width / 8 * 8;
	if (!mlx_resize_image(info->img, info->c.image_width, info->c.image_height))
		free_all(info);
	camera_render(info);
}

void camera_move(t_info *info, t_point point, float fov, t_vec3 orient)
{
	info->c.point = point;
	info->c.fov = fov;
	info->c.orient = orient;
	camera_render(info);
}
