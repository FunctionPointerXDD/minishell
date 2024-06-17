/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:08:47 by sihong            #+#    #+#             */
/*   Updated: 2023/10/07 14:08:59 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	haystack_i;
	size_t	needle_i;

	if (needle[0] == 0)
		return ((char *)haystack);
	if (haystack == 0 && len == 0)
		return (0);
	haystack_i = 0;
	while (haystack[haystack_i] && haystack_i < len)
	{
		needle_i = 0;
		while (needle[needle_i])
		{
			if (haystack[haystack_i + needle_i] != needle[needle_i])
				break ;
			if (needle[needle_i + 1] == 0)
				return ((char *)&haystack[haystack_i]);
			if (haystack[haystack_i + needle_i] == 0
				|| haystack_i + needle_i + 1 >= len)
				break ;
			needle_i++;
		}
		haystack_i++;
	}
	return (0);
}
