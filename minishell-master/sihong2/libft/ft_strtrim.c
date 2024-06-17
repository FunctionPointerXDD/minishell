/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:59:07 by sihong            #+#    #+#             */
/*   Updated: 2023/10/08 15:59:13 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	set_point(char **anchor_front, char **anchor_back,
	char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (is_in_set(s1[i], set) && s1[i] != 0)
		i++;
	if (s1[i] == 0)
		return (1);
	*anchor_front = (char *)&s1[i];
	i = ft_strlen(s1) - 1;
	while (is_in_set(s1[i], set) && s1[i] != 0)
		i--;
	*anchor_back = (char *)&s1[i];
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		count;
	char	*anchor_front;
	char	*anchor_back;
	char	*temp;

	if (set_point(&anchor_front, &anchor_back, s1, set))
	{
		temp = (char *)ft_calloc(1, sizeof(char));
		if (temp == 0)
			return (0);
		return (temp);
	}
	count = 0;
	while (anchor_front + count != anchor_back + 1)
		count++;
	temp = (char *)ft_calloc(count + 1, sizeof(char));
	if (temp == 0)
		return (0);
	i = -1;
	while (anchor_front + ++i != anchor_back + 1)
		temp[i] = anchor_front[i];
	return (temp);
}
