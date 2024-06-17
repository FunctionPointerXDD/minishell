/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:19:47 by chansjeo          #+#    #+#             */
/*   Updated: 2024/02/09 15:47:06 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;

	len_needle = ft_strlen(needle);
	if (len_needle == 0)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (*haystack && len >= len_needle)
	{
		len--;
		if (ft_memcmp(haystack, needle, len_needle) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
