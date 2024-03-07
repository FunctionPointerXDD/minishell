/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:58:40 by chansjeo          #+#    #+#             */
/*   Updated: 2024/01/31 11:53:12 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	res;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	res = dst_len + src_len;
	if (dst_len >= dstsize)
		return (src_len + dstsize);
	dst += dst_len;
	dstsize -= dst_len;
	if (src_len >= dstsize)
		src_len = dstsize - 1;
	ft_memcpy(dst, src, src_len);
	dst[src_len] = '\0';
	return (res);
}
