/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:48:32 by mquero            #+#    #+#             */
/*   Updated: 2024/11/05 15:01:15 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	l;
	char			*str;

	l = ft_strlen(s);
	if (start >= l)
		return (ft_strdup(""));
	else if (len <= l && (l - start) >= len)
		str = (char *)ft_calloc((len + 1), sizeof(char));
	else
		str = (char *)ft_calloc((l - start + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
