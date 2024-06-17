/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 20:47:59 by sihong            #+#    #+#             */
/*   Updated: 2023/10/06 20:49:12 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;

	temp = (char *)s;
	while (*temp)
		temp++;
	while (1)
	{
		if (*temp == (unsigned char)c)
			return (temp);
		if (temp == (char *)s)
			return (0);
		temp--;
	}
}
