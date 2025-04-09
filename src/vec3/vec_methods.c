/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_methods.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:47:27 by mquero            #+#    #+#             */
/*   Updated: 2025/04/09 09:47:28 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>

inline t_vec3	vec3_new(float x, float y, float z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

inline float	vec3_length(t_vec3 vec)
{
	return (sqrtf(vec3_length_squared(vec)));
}

inline t_vec3	vec3_flip_minus(t_vec3 vec)
{
	return (vec3_new(-vec.x, -vec.y, -vec.z));
}

inline float	vec3_length_squared(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
