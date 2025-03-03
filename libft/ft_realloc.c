/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:06:52 by mquero            #+#    #+#             */
/*   Updated: 2025/03/03 20:07:56 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_realloc(void *ptr, size_t size)
{
    void *new_ptr;

    if (size == 0)
    {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;
    if (ptr)
    {
        ft_memcpy(new_ptr, ptr, size);
        free(ptr);
    }
    return (new_ptr);
}