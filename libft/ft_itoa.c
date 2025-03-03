/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:41:53 by mquero            #+#    #+#             */
/*   Updated: 2024/10/30 14:49:45 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	allocate(char *num, int i, int neg, long int n)
{
	num[i] = '\0';
	while (n > 9)
	{
		num[i - 1] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	i--;
	if (neg == '-')
	{
		num[0] = neg;
	}
	if (n < 10 && n >= 0)
		num[i] = n + '0';
}

char	*ft_itoa(int n)
{
	long long	hold;
	long long	k;
	int			i;
	char		*num;
	char		neg;

	k = n;
	i = 1;
	if (k < 0)
	{
		neg = '-';
		k = k * -1;
		i++;
	}
	hold = k;
	while (hold > 9)
	{
		hold = hold / 10;
		i++;
	}
	num = (char *)malloc((i + 1) * sizeof(char));
	if (num == NULL)
		return (NULL);
	allocate(num, i, neg, k);
	return (num);
}
