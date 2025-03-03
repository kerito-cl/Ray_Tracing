/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:50:18 by mquero            #+#    #+#             */
/*   Updated: 2024/10/29 11:23:48 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int			i;
	const char	*s;
	char		*d;

	if (dest == NULL && src == NULL)
		return (dest);
	i = 0;
	d = dest;
	s = src;
	while (i < (int)n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
