/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:30:56 by sihong            #+#    #+#             */
/*   Updated: 2023/10/27 17:31:13 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

char	*ft_uitoa(unsigned int n)
{
	long long	n_temp;
	size_t		len;
	char		*result;

	n_temp = (long long)n;
	len = find_len(n_temp);
	n_temp = (long long)n;
	result = (char *)ft_calloc(len + 1, sizeof(char));
	if (result == 0)
		return (0);
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
