/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:33:08 by mquero            #+#    #+#             */
/*   Updated: 2024/10/29 17:51:23 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	k;
	size_t	len;

	k = 0;
	i = ft_strlen(dst);
	len = ft_strlen(src);
	if (size == 0)
		return (len);
	if (i >= size)
		return (size + len);
	while (src[k] && ((i + k) < (size - 1)))
	{
		dst[i + k] = src[k];
		k++;
	}
	if (i < size)
		dst[i + k] = '\0';
	return (len + i);
}
