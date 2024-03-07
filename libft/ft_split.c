/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:32:00 by chansjeo          #+#    #+#             */
/*   Updated: 2023/11/27 14:14:58 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *str, char c)
{
	int	count;

	count = 0;
	if (*str == c)
		count = -1;
	while (*str)
	{
		while (*str && *str != c)
			++str;
		while (*str && *str == c)
			++str;
		++count;
	}
	return (count);
}

static void	free_arr(char **str_arr, int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

static int	create_arr(char **str_arr, char const *str, char c, int count_words)
{
	int	len;
	int	i;

	i = 0;
	while (*str && i < count_words)
	{
		len = 0;
		while (*str && *str == c)
			str++;
		while (*str && *str != c)
		{
			str++;
			len++;
		}
		str_arr[i] = (char *)malloc(sizeof(char) * len + 1);
		if (str_arr[i] == 0)
		{
			free_arr(str_arr, i);
			return (0);
		}
		ft_strlcpy(str_arr[i], str - len, len + 1);
		++i;
	}
	str_arr[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str_array;
	int		count_words;

	count_words = count_word(s, c);
	str_array = (char **)malloc(sizeof(char *) * (count_words + 1));
	if (str_array == 0)
		return (0);
	if (create_arr(str_array, s, c, count_words) == 0)
		return (0);
	return (str_array);
}
