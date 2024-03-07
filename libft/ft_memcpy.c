/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:58:50 by chansjeo          #+#    #+#             */
/*   Updated: 2023/12/05 13:28:14 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*cp_dst;
	const unsigned char	*cp_src;

	cp_dst = dst;
	cp_src = src;
	if (dst == 0 && src == 0)
		return (0);
	while (n--)
		*cp_dst++ = *cp_src++;
	return (dst);
}
