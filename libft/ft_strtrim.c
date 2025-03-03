/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:00:12 by mquero            #+#    #+#             */
/*   Updated: 2024/10/30 14:50:41 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	trim_start(int i, char const *s1, char const *set)
{
	int	j;

	j = 0;
	while (set[j])
	{
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

int	trim_end(int i, char const*s1, char const *set)
{
	int	k;
	int	j;

	k = i;
	while (s1[i] != '\0')
	{
		k++;
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[k] == set[j])
				i = trim_start(k + 1, s1, set);
			else if (s1[k] == '\0')
				i = k;
			j++;
		}
		if (set[0] == '\0')
			i++;
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		i;
	int		j;
	int		y;

	i = 0;
	y = trim_start(i, s1, set);
	i = trim_end(y, s1, set);
	trimmed = (char *)malloc((i - y + 1) * sizeof(char));
	if (trimmed == NULL)
		return (NULL);
	j = 0;
	while (y < i)
	{
		trimmed[j] = s1[y];
		j++;
		y++;
	}
	trimmed[j] = '\0';
	return (trimmed);
}
