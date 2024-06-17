/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:14:23 by chansjeo          #+#    #+#             */
/*   Updated: 2023/10/23 16:52:59 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*us;

	us = (const unsigned char *)s;
	while (n--)
	{
		if (*us == (unsigned char)c)
			return ((void *)us);
		us++;
	}
	return (NULL);
}
