/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:42:43 by chansjeo          #+#    #+#             */
/*   Updated: 2024/01/23 16:56:25 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_memset(void *b, int c, size_t len)
{
	unsigned char	*ub;
	unsigned char	uc;

	ub = (unsigned char *)b;
	uc = (unsigned char)c;
	while (len--)
		*ub++ = uc;
	return (b);
}

char	*gnl_strchr(const char *s, int c)
{
	const unsigned char	*us;

	if (s == 0)
		return (0);
	us = (const unsigned char *)s;
	while (*us != (unsigned char)c)
	{
		if (*us == '\0')
			return (0);
		us++;
	}
	return ((char *)us);
}

char	*gnl_strdup(const char *s1)
{
	size_t	len;
	char	*res;
	char	*cp_res;

	len = 0;
	while (s1 && *s1++)
		len++;
	if (s1)
		s1 -= (len + 1);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == 0)
		return (0);
	else
	{
		cp_res = res;
		while (s1 && *s1)
			*cp_res++ = *s1++;
	}
	res[len] = '\0';
	return (res);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*cp_res;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	while (s1 && *s1++)
		len1++;
	if (s1)
		s1 -= (len1 + 1);
	while (s2 && *s2++)
		len2++;
	if (s2)
		s2 -= (len2 + 1);
	res = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (res == 0)
		return (0);
	cp_res = res;
	while (s1 && *s1)
		*cp_res++ = *s1++;
	while (s2 && *s2)
		*cp_res++ = *s2++;
	res[len1 + len2] = '\0';
	return (res);
}
