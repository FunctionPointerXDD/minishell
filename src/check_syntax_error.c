/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:23:44 by sihong            #+#    #+#             */
/*   Updated: 2024/02/07 18:24:02 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_paren(t_parse_list *head)
{
	while (head)
	{
		if (head->token_type == parenthesis && head->s[0] == '(')
		{
			head = head->next;
			while (check_blank(head))
				head = head->next;
			if (head == 0)
				return (0);
			if (head->token_type == parenthesis && head->s[0] == ')')
				return (0);
		}
		head = head->next;
	}
	return (1);
}

int	check_overlapped_paren(t_parse_list *head)
{
	while (head)
	{
		if (head->token_type == parenthesis && head->s[0] == '('
			&& head->next && head->next->token_type == parenthesis
			&& head->next->s[0] == '(')
		{
			while (head != 0
				&& !(head->token_type == parenthesis && head->s[0] == ')')
				&& !(head->token_type == parenthesis && head->s[0] == '('))
				head = head->next;
			if (head->next == 0)
				return (0);
			if (head->next->token_type == parenthesis && head->s[0] == ')')
				return (0);
		}
		head = head->next;
	}
	return (1);
}

int	check_tree_syntax_error(t_parse_tree *root)
{
	if (root->type == logical)
		return (0);
	while (root)
	{
		if (root->type != logical)
		{
			if (check_blank(root->lst) == 1 && root->lst->next == 0)
				return (0);
			if (root->right && root->right->type != logical)
				return (0);
		}
		else
		{
			if (root->right == 0)
				return (0);
			if (root->right->type == logical)
				return (0);
		}
		root = root->right;
	}
	return (1);
}

int	check_list_syntax_error_2(t_token_type tmp, t_parse_list *head)
{
	if ((tmp == redirection && (head->token_type != args \
		&& head->token_type != single_quote \
		&& head->token_type != double_quote))
		|| (tmp == pipex && head->token_type == logical)
		|| (tmp == pipex && head->token_type == pipex)
		|| (tmp == pipex && head->token_type == none)
		|| (tmp == logical && head->token_type == pipex)
		|| (tmp == logical && head->token_type == logical)
		|| (tmp == logical && head->token_type == none))
		return (0);
	return (1);
}

int	check_list_syntax_error(t_parse_list *head)
{
	t_token_type	tmp;

	if (check_empty_paren(head) == 0 || check_overlapped_paren(head) == 0)
		return (0);
	while (1)
	{
		tmp = head->token_type;
		head = head->next;
		while (head != 0 && check_blank(head) == 1)
			head = head->next;
		if (!head)
		{
			if (tmp == redirection || tmp == pipex || tmp == logical)
				return (0);
			break ;
		}
		if (check_list_syntax_error_2(tmp, head) == 0)
			return (0);
	}
	return (1);
}
