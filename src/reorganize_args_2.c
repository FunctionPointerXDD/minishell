/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganize_args_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:50:54 by sihong            #+#    #+#             */
/*   Updated: 2024/03/06 16:05:10 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_blank_after_pipex(t_parse_list *lst)
{
	t_parse_list	*tmp;

	while (lst)
	{
		if (lst->next && lst->token_type == pipex \
			&& check_blank(lst->next) == 1)
		{
			tmp = lst->next;
			lst->next = lst->next->next;
			free(tmp->s);
			free(tmp);
		}
		lst = lst->next;
	}
}

void	qoute_rollback_space(char **s)
{
	int		i;
	int		j;
	char	quote;

	i = -1;
	while (s[++i])
	{
		j = 0;
		while (s[i][j])
		{
			while (s[i][j] && s[i][j] != '\'' && s[i][j] != '\"')
				j++;
			if (s[i][j] == 0)
				continue ;
			quote = s[i][j];
			j++;
			while (s[i][j] != quote)
			{
				if (s[i][j] == 127)
					s[i][j] = ' ';
				j++;
			}
			j++;
		}
	}
}

void	quote_replace_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			s[i] = 127;
		i++;
	}
}
