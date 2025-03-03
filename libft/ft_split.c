/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:40:11 by mquero            #+#    #+#             */
/*   Updated: 2025/02/22 15:54:18 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	freesplit(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static int	countarr(int n, const char *s, char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			n++;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (n);
}

static char	*allocate(char const *s, char c, int *y)
{
	int		k;
	char	*temp;

	k = 0;
	while (s[*y] == c)
		*y = *y + 1;
	while (s[*y] != c && s[*y] != '\0')
	{
		k++;
		*y = *y + 1;
	}
	temp = (char *)malloc((k + 1) * (sizeof(char)));
	if (temp == NULL)
		return (NULL);
	ft_strlcpy(temp, (s + *y - k), k + 1);
	return (temp);
}

char	**ft_split(char const *s, char c)
{
	char	**strsplit;
	int		n;
	int		i;
	int		y;

	i = 0;
	n = 0;
	y = 0;
	n = countarr(n, s, c);
	strsplit = (char **)malloc((n + 1) * sizeof (char *));
	if (strsplit == NULL)
		return (NULL);
	strsplit[n] = NULL;
	while (i < n)
	{
		strsplit[i] = allocate((char *)s, c, &y);
		if (strsplit[i] == NULL)
		{
			freesplit(strsplit);
			return (NULL);
		}
		i++;
	}
	return (strsplit);
}
