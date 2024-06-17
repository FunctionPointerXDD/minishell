/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:35:55 by chansjeo          #+#    #+#             */
/*   Updated: 2023/12/13 13:05:19 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*us1;
	const unsigned char	*us2;

	while (n)
	{
		us1 = (const unsigned char *)s1++;
		us2 = (const unsigned char *)s2++;
		if (*us1 != *us2)
			return ((int)(*us1 - *us2));
		n--;
	}
	return (0);
}	
