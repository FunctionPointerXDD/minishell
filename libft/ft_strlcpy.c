/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:17:21 by chansjeo          #+#    #+#             */
/*   Updated: 2024/01/31 11:45:40 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	ret;

	src_len = 0;
	ret = ft_strlen(src);
	if (dstsize != 0)
	{
		if (ret >= dstsize)
			src_len = dstsize - 1;
		else
			src_len = ret;
		ft_memcpy(dst, src, src_len);
		dst[src_len] = '\0';
	}
	return (ret);
}
