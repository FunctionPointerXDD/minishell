/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:56:26 by chansjeo          #+#    #+#             */
/*   Updated: 2023/10/16 14:57:18 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	int		len;
	int		i;

	if (f == 0)
		return (0);
	len = ft_strlen(s);
	res = (char *)malloc(sizeof(char) * len + 1);
	if (res == 0)
		return (0);
	i = 0;
	while (*s)
	{
		res[i] = f(i, *s);
		i++;
		s++;
	}
	res[i] = '\0';
	return (res);
}
