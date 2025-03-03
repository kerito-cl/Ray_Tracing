/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:43:45 by mquero            #+#    #+#             */
/*   Updated: 2024/10/30 11:21:30 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;
	int	j;

	i = 0;
	if (*little == 0)
		return ((char *)big);
	while (i < (int)len)
	{
		j = 0;
		while (little[j] == (char)big[i + j])
		{
			j++;
			if (j + i > (int)len)
				return (NULL);
			else if ((char)little[j] == '\0')
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
