/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:55:07 by chansjeo          #+#    #+#             */
/*   Updated: 2023/10/14 19:39:19 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*cp_dst;
	const unsigned char	*cp_src;

	cp_dst = dst;
	cp_src = src;
	if (dst == 0 && src == 0)
		return (0);
	if (cp_dst <= cp_src)
	{
		while (len--)
			*cp_dst++ = *cp_src++;
	}
	else
	{
		cp_dst += len;
		cp_src += len;
		while (len--)
			*--cp_dst = *--cp_src;
	}
	return (dst);
}
