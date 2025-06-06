/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:46:26 by mquero            #+#    #+#             */
/*   Updated: 2025/04/09 09:46:27 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "mini_rt.h"

void			camera_init(t_cam *c);
t_ray			camera_get_ray(t_cam *c, int i, int j);
t_color			camera_ray_color(t_info *info, t_ray ray, t_obj **world,
					int depth);

unsigned int	get_color(t_vec3 vec)
{
	return (((uint8_t)(vec.x * 255) << 24) | ((uint8_t)(vec.y
				* 255) << 16) | ((uint8_t)(vec.z * 255) << 8) | 255);
}

// @details to render by iterate all the pixels.
void	camera_render(t_info *info)
{
	int			j;
	int			i;
	t_ray		ray;
	t_color		color;
	uint32_t	packed_color;

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
			packed_color = get_color(color);
			mlx_put_pixel(info->img, i, j, packed_color);
			++i;
		}
		++j;
	}
}

void	camera_start(t_info *info)
{
	info->c.image_height = DEFAULT_HEIGHT;
	info->c.image_width = DEFAULT_WIDTH;
	info->mlx = mlx_init(DEFAULT_WIDTH, DEFAULT_HEIGHT, "KD MiniRT", true);
	info->img = mlx_new_image(info->mlx, info->c.image_width,
			info->c.image_height);
	if (!info->img || mlx_image_to_window(info->mlx, info->img, 0, 0) < 0)
		free_all(info);
	camera_render(info);
}

void	camera_resize_screen(t_info *info, int image_width, int image_height)
{
	info->c.image_height = image_height / THREADS_AMOUNT * THREADS_AMOUNT;
	info->c.image_width = image_width / THREADS_AMOUNT * THREADS_AMOUNT;
	if (!mlx_resize_image(info->img, info->c.image_width, info->c.image_height))
		free_all(info);
	camera_render(info);
}
