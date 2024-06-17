/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:38:31 by sihong            #+#    #+#             */
/*   Updated: 2023/10/07 13:38:37 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (1)
	{
		if (*(unsigned char *)(s1 + i) != *(unsigned char *)(s2 + i)
			|| i == n - 1)
			return (*(unsigned char *)(s1 + i)
				- *(unsigned char *)(s2 + i));
		i++;
	}
}
