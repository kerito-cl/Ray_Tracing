/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:47:57 by mquero            #+#    #+#             */
/*   Updated: 2025/04/09 09:47:58 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	clamp(float n, float min, float max);

t_color	texutre_constant_color(t_info *info, t_material *mat, t_hit_record *rec)
{
	(void)rec;
	return (mat->albedo);
}

t_color	texture_checker_color(t_info *info, t_material *mat, t_hit_record *rec)
{
	float	inv_scale;
	int		res;

	inv_scale = 1.0f / CHECK_SCALE;
	if (rec->uv_chess_board)
		res = (int)floorf(rec->u * inv_scale) + (int)floorf(rec->v * inv_scale);
	else
		res = (int)floorf(rec->p.x * inv_scale) + (int)floorf(rec->p.y
				* inv_scale) + (int)floorf(rec->p.z * inv_scale);
	if (res % 2 == 0)
		return (mat->albedo);
	return (mat->albedo2);
}

t_color	texture_img_color(t_info *info, t_material *mat, t_hit_record *rec)
{
	mlx_texture_t	*texture;
	int				x;
	int				y;
	int				index;

	texture = info->textures[mat->texture_img_idx];
	rec->u = clamp(rec->u, 0.0f, 1.0f);
	rec->v = 1.0f - clamp(rec->v, 0.0f, 1.0f);
	x = (int)(rec->u * texture->width);
	y = (int)(rec->v * texture->height);
	if (x >= (int)texture->width)
		x = texture->width - 1;
	if (y >= (int)texture->height)
		y = texture->height - 1;
	index = (y * texture->width + x) * texture->bytes_per_pixel;
	return (vec3_new(texture->pixels[index + 0] / 255.0f, texture->pixels[index
				+ 1] / 255.0f, texture->pixels[index + 2] / 255.0f));
}
