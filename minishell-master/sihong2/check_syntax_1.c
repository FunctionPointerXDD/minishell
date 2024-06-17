/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:23:44 by sihong            #+#    #+#             */
/*   Updated: 2024/02/07 18:24:02 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_blank(t_parse_list *node)
{
	int	i;

	if (node->token_type == args)
	{
		i = 0;
		while (node->s[i] == ' ')
			i += 1;
		if (node->s[i] == 0)
			return (1);
	}
	return (0);
}

int	check_pattern_error(t_parse_list *head)
{
	t_token_type	tmp;

	while (1)
	{
		tmp = head->token_type;
		head = head->next;
		while (head != 0 && skip_blank(head) == 1)
			head = head->next;
		if (!head)
			break ;
		if ((tmp == redirection && head->token_type == redirection)
			|| (tmp == redirection && head->token_type == pipex)
			|| (tmp == redirection && head->token_type == logical)
			|| (tmp == redirection && head->token_type == parenthesis)
			|| (tmp == pipex && head->token_type == logical)
			|| (tmp == logical && head->token_type == redirection)
			|| (tmp == logical && head->token_type == pipex)
			|| (tmp == logical && head->token_type == logical))
			return (0);
	}
	return (1);
}

int	check_parenthesis_error(t_parse_list *head)
{
	int				hint;

	hint = 0;
	while (1)
	{
		while (head != 0 && head->token_type != parenthesis)
			head = head->next;
		if (!head)
			break ;
		hint += 1;
		if (hint % 2 == 1 && head->s[0] == ')')
			return (0);
		if (hint % 2 == 0 && head->s[0] == '(')
			return (0);
	}
	if (hint % 2 == 1)
		return (0);
	else
		return (1);
}

int	check_syntax_1(t_parse_list *head)
{
	if (check_pattern_error(head) == 0)
		return (0);
	if (check_parenthesis_error(head) == 0)
		return (0);
	return (1);
}
