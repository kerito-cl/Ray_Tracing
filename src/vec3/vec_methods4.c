/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_methods4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xifeng <xifeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:47:39 by mquero            #+#    #+#             */
/*   Updated: 2025/04/09 14:40:09 by xifeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>

inline t_vec3	vec3_random(void)
{
	return (vec3_new(random_float(), random_float(), random_float()));
}

inline t_vec3	vec3_random_range(float min, float max)
{
	return (vec3_new(random_float_range(min, max), random_float_range(min, max),
			random_float_range(min, max)));
}

inline t_vec3	vec3_random_unit_vector(void)
{
	t_vec3	vec;
	float	len_sq;

	while (1)
	{
		vec = vec3_random_range(-1, 1);
		len_sq = vec3_length_squared(vec);
		if (len_sq > 1e-12 && len_sq <= 1)
			return (vec3_div_vec(vec, sqrtf(len_sq)));
	}
}

inline t_vec3	vec3_min(t_vec3 vec1, t_vec3 vec2)
{
	return (vec3_new(fminf(vec1.x, vec2.x), fminf(vec1.y, vec2.y), fminf(vec1.z,
				vec2.z)));
}

inline t_vec3	vec3_max(t_vec3 vec1, t_vec3 vec2)
{
	return (vec3_new(fmaxf(vec1.x, vec2.x), fmaxf(vec1.y, vec2.y), fmaxf(vec1.z,
				vec2.z)));
}
