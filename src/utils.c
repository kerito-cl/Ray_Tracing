/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:35:21 by mquero            #+#    #+#             */
/*   Updated: 2025/03/03 23:18:39 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void    new_vec3(t_vec3 *vec3, char **cvec, bool *isvalid ,bool if_rgb)
{
    if (!cvec[0] || !cvec[1] || !cvec[2] || cvec[3] != NULL)
    {
        freesplit(cvec);
        *isvalid = false;
        return ;
    }
    vec3->x = ft_strtof(cvec[0], NULL);
    vec3->y = ft_strtof(cvec[1], NULL);
    vec3->z = ft_strtof(cvec[2], NULL);
    if (if_rgb)
    {
        vec3->x = ft_strtof(cvec[0], NULL) / 255;
        vec3->y = ft_strtof(cvec[1], NULL) / 255;
        vec3->z = ft_strtof(cvec[2], NULL) / 255;
    }
    if (cvec != NULL)
        freesplit(cvec);
}