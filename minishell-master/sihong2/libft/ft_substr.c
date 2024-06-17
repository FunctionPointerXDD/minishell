/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:23:17 by sihong            #+#    #+#             */
/*   Updated: 2023/10/08 14:23:20 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*tmp;
	size_t			i;

	if (start > ft_strlen(s))
		len = 0;
	else if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	tmp = (char *)ft_calloc((len + 1), sizeof(char));
	if (tmp == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		tmp[i] = s[start + i];
		if (s[start + i] == 0)
			return (tmp);
		i++;
	}
	return (tmp);
}
