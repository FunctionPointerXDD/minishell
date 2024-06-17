/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:44:31 by sihong            #+#    #+#             */
/*   Updated: 2024/02/27 19:06:57 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	is_sign_negative(long long *n_temp, int *sign, size_t *len)
{
	if (*n_temp < 0)
	{
		*n_temp *= -1;
		*sign = -1;
		*len += 1;
	}
}

static size_t	find_len(long long n_temp)
{
	size_t	len;

	if (n_temp == 0)
		return (1);
	len = 0;
	while (n_temp)
	{
		n_temp /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			sign;
	long long	n_temp;
	size_t		len;
	char		*result;

	n_temp = (long long)n;
	len = find_len(n_temp);
	n_temp = (long long)n;
	is_sign_negative(&n_temp, &sign, &len);
	result = (char *)ft_calloc(len + 1, sizeof(char));
	if (result == 0)
		return (0);
	if (sign == -1)
		result[0] = '-';
	if (n_temp == 0)
		result[0] = '0';
	while (n_temp)
	{
		--len;
		result[len] = n_temp % 10 + '0';
		n_temp /= 10;
	}
	return (result);
}
