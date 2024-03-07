/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse_wild_card_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:01:00 by sihong            #+#    #+#             */
/*   Updated: 2024/03/06 19:15:24 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_key_2(char *s, char *key, int start, int end)
{
	int		i;
	int		j;
	char	quote;

	i = start;
	j = 0;
	while (i < end)
	{
		while (s[i] == '\"' || s[i] == '\'')
		{
			quote = s[i];
			while (s[++i] != quote)
				key[j++] = s[i];
			i += 1;
		}
		if (i >= end)
			break ;
		key[j++] = s[i];
		i += 1;
	}
}

char	*get_key(char *s, int start, int end)
{
	int		len;
	char	*key;

	len = get_key_len(s, start, end);
	if (len == 0)
		return (0);
	key = ft_calloc_adv(len + 1, sizeof(char));
	get_key_2(s, key, start, end);
	return (key);
}

void	get_key_lst_skip_quote(char *s, int *i)
{
	char	quote;

	if (s[*i] == '\"' || s[*i] == '\'')
	{
		quote = s[*i];
		*i += 1;
		while (s[*i] != quote)
			*i += 1;
	}
}

int	get_key_lst_make_key_node(char *s, int *i, int *anchor, \
		t_wild_key_lst **key_tmp)
{
	if (s[*i] == '*')
	{
		if (*i != 0)
		{
			(*key_tmp)->key = get_key(s, *anchor, *i);
			if ((*key_tmp)->key != 0)
			{
				(*key_tmp)->next = ft_calloc_adv(1, sizeof(t_wild_key_lst));
				*key_tmp = (*key_tmp)->next;
			}
		}
		(*key_tmp)->wild = 1;
		while (s[*i] == '*')
			*i += 1;
		*anchor = *i;
		if (s[*anchor] == 0)
			return (0);
		(*key_tmp)->next = ft_calloc_adv(1, sizeof(t_wild_key_lst));
		*key_tmp = (*key_tmp)->next;
		*i -= 1;
	}
	return (1);
}

t_wild_key_lst	*get_key_lst(char *s)
{
	t_wild_key_lst	*wild_key_lst;
	t_wild_key_lst	*key_tmp;
	int				i;
	int				anchor;

	wild_key_lst = ft_calloc_adv(1, sizeof(t_wild_key_lst));
	key_tmp = wild_key_lst;
	i = 0;
	anchor = 0;
	while (s[i])
	{
		get_key_lst_skip_quote(s, &i);
		if (get_key_lst_make_key_node(s, &i, &anchor, &key_tmp) == 0)
			break ;
		if (anchor != i + 1 && s[i + 1] == 0)
			key_tmp->key = get_key(s, anchor, i + 1);
		i += 1;
	}
	if (wild_key_lst->wild == 0 && wild_key_lst->next == 0)
	{
		free(wild_key_lst->key);
		free(wild_key_lst);
		return (0);
	}
	return (wild_key_lst);
}
