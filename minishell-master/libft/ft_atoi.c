/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:34:14 by chansjeo          #+#    #+#             */
/*   Updated: 2023/12/13 12:13:16 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				neg;
	unsigned long	dec;
	unsigned long	ret;

	neg = 1;
	ret = 0;
	while (*str == ' ' || *str == '\t' || *str == '\r' || \
			*str == '\n' || *str == '\v' || *str == '\f')
		++str;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		++str;
	}
	while (1)
	{
		dec = *(str++) - '0';
		if (dec > 9)
			break ;
		ret *= 10;
		ret += dec;
	}
	return ((int)(neg * ret));
}
