/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:08:10 by sihong            #+#    #+#             */
/*   Updated: 2024/03/07 13:06:08 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_line_2(t_parse_tree **root)
{
	if (make_complete_parse_tree(root) == 1)
	{
		write(2, "minishell : syntax error\n", 25);
		free_parse_tree(*root);
		return (0);
	}
	return (1);
}

t_parse_tree	*parse_line(char *line)
{
	t_parse_list	*head;
	t_parse_tree	*root;

	head = seperate_quote(line);
	if (head == 0)
		return (0);
	head = seperate_others(head);
	if (check_list_syntax_error(head) == 0)
	{
		write(2, "minishell : syntax error\n", 25);
		free_parse_list(head);
		return (0);
	}
	head = reorganize_args(head);
	root = make_basic_parse_tree(head);
	if (root == 0)
	{
		write(2, "minishell : syntax error\n", 25);
		return (0);
	}
	if (parse_line_2(&root) == 0)
		return (0);
	return (root);
}
