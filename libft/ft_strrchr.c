/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:23:48 by mquero            #+#    #+#             */
/*   Updated: 2024/11/05 15:01:05 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	int		i;
	int		flag;

	flag = -1;
	i = 0;
	p = (char *)s;
	while (p[i])
	{
		if (p[i] == (unsigned char)c)
			flag = i;
		i++;
	}
	if (p[i] == (unsigned char)c)
		return (p + i);
	else if (flag != -1)
		return (p + flag);
	return (NULL);
}
