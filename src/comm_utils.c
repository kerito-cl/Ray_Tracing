/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xifeng <xifeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:16:40 by xifeng            #+#    #+#             */
/*   Updated: 2025/04/09 14:57:19 by xifeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "mini_rt.h"
#include <stdlib.h>

// @brief degree to radius
inline float	degree_to_radius(float degree)
{
	return (degree * PI / 180.0f);
}

// @brief returns a random float
inline float	random_float(void)
{
	return ((float)rand() / (float)(RAND_MAX + 1.0));
}

// @brief returns a random float between min to max.
inline float	random_float_range(float min, float max)
{
	return ((float)(min + (max - min) * random_float()));
}
