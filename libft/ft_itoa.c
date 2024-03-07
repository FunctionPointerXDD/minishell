/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:32:19 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/07 13:30:15 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	length(long n)
{
	int		len;

	len = 0;
	if (n <= 0)
	{
		len = 1;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		tmp;
	int		len;
	long	num;
	char	*res;

	num = n;
	len = length(num);
	if (num < 0)
		num = -num;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == 0)
	{
		perror("malloc");
		exit(1);
	}
	res[len] = '\0';
	while (len--)
	{
		tmp = num % 10;
		res[len] = tmp + '0';
		num /= 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
