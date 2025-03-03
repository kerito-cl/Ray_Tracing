/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:35:21 by mquero            #+#    #+#             */
/*   Updated: 2025/02/27 14:28:10 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void    new_vec3(t_vec3 *vec3, char **cvec, bool if_rgb)
{
    vec3->x = strtod(cvec[0], NULL);
    vec3->y = strtod(cvec[1], NULL);
    vec3->z = strtod(cvec[2], NULL);
    if (if_rgb)
    {
        vec3->x = strtod(cvec[0], NULL) / 255;
        vec3->y = strtod(cvec[1], NULL) / 255;
        vec3->z = strtod(cvec[2], NULL) / 255;
    }
    if (cvec != NULL)
        freesplit(cvec);
}