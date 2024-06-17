/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 20:30:57 by sihong            #+#    #+#             */
/*   Updated: 2023/10/06 20:31:05 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	set_dstsize(size_t dstsize, size_t dst_count)
{
	if (dstsize == dst_count + 1)
		return (dstsize - 1);
	return (dstsize);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_count;
	size_t	src_count;
	size_t	i;

	if (dst == 0)
		dst_count = 0;
	else
		dst_count = ft_strlen(dst);
	src_count = ft_strlen(src);
	if (dstsize <= dst_count + 1)
		return (set_dstsize(dstsize, dst_count) + src_count);
	i = 0;
	while (1)
	{
		dst[i + dst_count] = src[i];
		if (src[i] == '\0')
			break ;
		i++;
		if (dst_count + i == dstsize - 1)
		{
			dst[i + dst_count] = '\0';
			break ;
		}
	}
	return (dst_count + src_count);
}
