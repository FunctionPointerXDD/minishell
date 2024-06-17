/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:29:41 by chansjeo          #+#    #+#             */
/*   Updated: 2023/10/15 19:01:59 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	u1;
	unsigned char	u2;

	while (n)
	{
		u1 = *s1++;
		u2 = *s2++;
		if (u1 != u2)
		{
			if (u1 > u2)
				return (1);
			else
				return (-1);
		}
		if (u1 == '\0')
			break ;
		n--;
	}
	return (0);
}
