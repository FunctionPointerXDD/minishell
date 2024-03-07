/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:14:14 by chansjeo          #+#    #+#             */
/*   Updated: 2024/02/09 11:21:16 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_check(char s1, char const *set)
{
	while (*set)
	{
		if (s1 == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*res;
	char const	*ofs;
	int			len;

	if (s1 == 0 || set == 0)
		return (0);
	len = ft_strlen(s1);
	while (set_check(*s1, set) == 1)
	{
		s1++;
		len--;
	}
	ofs = s1;
	s1 += len - 1;
	while (len > 0 && set_check(*s1, set) == 1)
	{
		s1--;
		len--;
	}
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == 0)
		return (0);
	ft_memset(res, 0, len + 1);
	ft_memcpy(res, ofs, len);
	return (res);
}
