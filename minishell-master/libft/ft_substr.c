/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:17:56 by chansjeo          #+#    #+#             */
/*   Updated: 2024/02/09 11:00:53 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* start --> string start point */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start > s_len)
	{
		len = 0;
		s += s_len;
	}
	else if (len + start > s_len)
	{
		len = s_len - start;
		s += start;
	}
	else
		s += start;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (0);
	ft_strlcpy(res, s, len + 1);
	return (res);
}
