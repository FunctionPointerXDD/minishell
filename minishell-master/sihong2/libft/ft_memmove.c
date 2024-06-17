/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:28:19 by sihong            #+#    #+#             */
/*   Updated: 2023/10/06 17:28:23 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if ((dst == 0 && src == 0))
		return (0);
	if (len == 0)
		return (dst);
	if (dst > src)
	{
		i = len - 1;
		while (1)
		{
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			if (i == 0)
				break ;
			i--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
