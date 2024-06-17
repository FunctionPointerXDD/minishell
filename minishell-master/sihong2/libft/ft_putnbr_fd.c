/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:17:59 by sihong            #+#    #+#             */
/*   Updated: 2023/10/09 14:18:15 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		c;
	long long	n_temp;

	n_temp = (long long)n;
	if (n_temp < 0)
	{
		write(fd, "-", 1);
		n_temp *= -1;
	}
	if (n_temp / 10 != 0)
		ft_putnbr_fd(n_temp / 10, fd);
	c = n_temp % 10 + '0';
	write(fd, &c, 1);
}
