/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:17:08 by sihong            #+#    #+#             */
/*   Updated: 2023/10/06 18:19:15 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	i;

	count = 0;
	while (src[count])
		count++;
	i = -1;
	if (dstsize > count)
	{
		while (++i < count)
			dst[i] = src[i];
	}
	else if (dstsize == 0)
		return (count);
	else
	{
		while (++i < dstsize - 1)
			dst[i] = src[i];
	}
	dst[i] = '\0';
	return (count);
}
