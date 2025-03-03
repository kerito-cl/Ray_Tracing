/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:13:59 by mquero            #+#    #+#             */
/*   Updated: 2024/11/05 15:00:15 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int		i;
	char	*s;
	char	*c;

	s = (char *)s1;
	c = (char *)s2;
	i = 0;
	while (i < (int)n)
	{
		if (s[i] != c[i])
			return ((unsigned char)s[i] - (unsigned char)c[i]);
		i++;
	}
	return (0);
}
