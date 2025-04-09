/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrics_supp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:47:05 by mquero            #+#    #+#             */
/*   Updated: 2025/04/09 09:47:07 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	cal_quadratic(float a, float b, float c, float t[2])
{
	float	discriminant;
	float	inv2a;
	float	temp;

	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (false);
	discriminant = sqrtf(discriminant);
	inv2a = 0.5 / a;
	t[0] = (-b - discriminant) * inv2a;
	t[1] = (-b + discriminant) * inv2a;
	if (t[0] > t[1])
	{
		temp = t[0];
		t[0] = t[1];
		t[1] = temp;
	}
	return (true);
}
