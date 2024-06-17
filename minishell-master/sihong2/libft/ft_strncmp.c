/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:14:42 by sihong            #+#    #+#             */
/*   Updated: 2023/10/06 21:14:48 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (0);
	while (1)
	{
		if (count == n)
		{
			count--;
			break ;
		}
		if (s1[count] != s2[count])
			break ;
		if (s1[count] == 0 || s2[count] == 0)
			break ;
		count++;
	}
	return ((unsigned char)s1[count] - (unsigned char)s2[count]);
}
