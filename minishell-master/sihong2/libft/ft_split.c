/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:53:36 by sihong            #+#    #+#             */
/*   Updated: 2023/10/08 18:53:40 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	free_data(char **result, int word_index)
{
	int	i;

	i = -1;
	while (++i < word_index)
		free(result[i]);
	free(result);
	return (1);
}

static int	set_single_arr(char **result, char const *s, char c)
{
	int		i;
	size_t	count;
	int		word_index;

	i = -1;
	count = 0;
	word_index = 0;
	while (s[++i])
	{
		if (s[i] == c && s[i + 1] == c)
			continue ;
		count++;
		if (s[i] == c || s[i + 1] == 0)
		{
			if (s[i] != c && s[i + 1] == 0)
				count++;
			result[word_index] = (char *)ft_calloc(count, sizeof(char));
			if (result[word_index] == 0)
				return (free_data(result, word_index));
			word_index++;
			count = 0;
		}
	}
	return (0);
}

static void	put_data(char **result, char const *s, char c)
{
	int	i;
	int	char_index;
	int	word_index;

	i = -1;
	char_index = 0;
	word_index = 0;
	while (s[++i])
	{
		if (s[i] == c && s[i + 1] == c)
			continue ;
		result[word_index][char_index] = s[i];
		if (s[i] == c || s[i + 1] == 0)
		{
			if (s[i] != c && s[i + 1] == 0)
				char_index++;
			result[word_index][char_index] = 0;
			word_index++;
			char_index = -1;
		}
		char_index++;
	}
}

static void	find_size(char const *s, char c, size_t *result_size)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (s[++i])
	{
		if (s[i] != c)
			check = 1;
		if (s[i] == c && s[i + 1] == c)
			continue ;
		if (s[i] == c && s[i + 1] != 0)
			(*result_size)++;
	}
	if (check == 1)
		(*result_size)++;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		temp;
	size_t	result_size;
	char	**result;

	if (s == 0)
	{
		result = (char **)ft_calloc(1, sizeof(char *));
		if (result == 0)
			return (0);
		return (result);
	}
	i = 0;
	while (s[i] == c && s[i] != 0)
		i++;
	temp = i;
	result_size = 0;
	find_size(&s[temp], c, &result_size);
	result = (char **)ft_calloc(result_size + 1, sizeof(char *));
	if (result == 0)
		return (0);
	if (set_single_arr(result, &s[temp], c))
		return (0);
	put_data(result, &s[temp], c);
	return (result);
}
