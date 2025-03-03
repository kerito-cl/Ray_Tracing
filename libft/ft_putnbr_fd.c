/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:34:19 by mquero            #+#    #+#             */
/*   Updated: 2024/10/30 16:15:09 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	k;
	char		p;
	int			rem;

	k = n;
	if (k < 0)
	{
		write(fd, "-", 1);
		k = k * -1;
	}
	if (k < 10 && k >= 0)
	{
		p = k + '0';
		write(fd, &p, 1);
	}
	if (k > 9)
	{
		ft_putnbr_fd(k / 10, fd);
		rem = (k % 10) + '0';
		write(fd, &rem, 1);
	}
}
