/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:37:39 by mquero            #+#    #+#             */
/*   Updated: 2025/03/03 20:56:42 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

static void	loop_assign(const char **str, int *sign, int *has_decimal)
{
	*has_decimal = 0;
	while (ft_isspace(**str))
		*str = *str + 1;
	if (**str == '-')
	{
		*sign = -1;
		*str = *str + 1;
	}
	else if (**str == '+')
		*str = *str + 1;
}

float	ft_strtof(const char *str, char **endptr)
{
	float	result;
	float	fraction;
	int		sign;
	int		has_decimal;

	result = 0.0;
	fraction = 0.1;
	sign = 1;
	loop_assign(&str, &sign, &has_decimal);
	while (ft_isdigit(*str) || (*str == '.' && !has_decimal))
	{
		if (*str == '.')
			has_decimal = 1;
		else if (!has_decimal)
			result = result * 10.0 + (*str - '0');
		else
		{
			result += (*str - '0') * fraction;
			fraction *= 0.1;
		}
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}
