/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_methods5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:47:42 by mquero            #+#    #+#             */
/*   Updated: 2025/04/09 09:47:43 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>

inline t_vec3	vec3_reflect(t_vec3 v, t_vec3 n)
{
	t_vec3	vec;

	vec = vec3_mul_vec(n, 2 * vec3_dot(v, n));
	return (vec3_sub_vecs(v, vec));
}

inline t_vec3	vec3_refract(t_vec3 uv, t_vec3 n, float etai_over_etat)
{
	float	cos_theta;
	t_vec3	r_out_perp;
	t_vec3	r_out_parallel;

	cos_theta = fminf(vec3_dot(vec3_flip_minus(uv), n), 1.0);
	r_out_perp = vec3_mul_vec(vec3_add_vecs(uv, vec3_mul_vec(n, cos_theta)),
			etai_over_etat);
	r_out_parallel = vec3_mul_vec(n, -sqrtf(fabsf((float)1.0
					- vec3_length_squared(r_out_perp))));
	return (vec3_add_vecs(r_out_perp, r_out_parallel));
}

inline t_color	vec3_mul_colors(t_vec3 vec1, t_vec3 vec2)
{
	t_color	color;

	color.x = vec1.x * vec2.x;
	if (color.x > 1)
		color.x = 1;
	color.y = vec1.y * vec2.y;
	if (color.y > 1)
		color.y = 1;
	color.z = vec1.z * vec2.z;
	if (color.z > 1)
		color.z = 1;
	return (color);
}
