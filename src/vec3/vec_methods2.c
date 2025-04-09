/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_methods2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:47:30 by mquero            #+#    #+#             */
/*   Updated: 2025/04/09 09:47:31 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>

inline t_vec3	vec3_add_vecs(t_vec3 vec1, t_vec3 vec2)
{
	return (vec3_new(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z));
}

inline t_vec3	vec3_sub_vecs(t_vec3 vec1, t_vec3 vec2)
{
	return (vec3_new(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z));
}

inline t_vec3	vec3_mul_vecs(t_vec3 vec1, t_vec3 vec2)
{
	return (vec3_new(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z));
}

inline t_vec3	vec3_div(float number, t_vec3 vec)
{
	return (vec3_new(number / vec.x, number / vec.y, number / vec.z));
}
