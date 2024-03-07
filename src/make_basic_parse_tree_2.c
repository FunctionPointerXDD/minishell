/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_basic_parse_tree_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:17:52 by sihong            #+#    #+#             */
/*   Updated: 2024/02/12 19:18:02 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	balance_parse_tree(t_parse_tree **root)
{
	t_parse_tree	*tmp;

	if (*root == 0 || (*root)->right == 0)
		return ;
	if ((*root)->right != 0
		&& ((*root)->type == organized_args || (*root)->type == parenthesis))
	{
		tmp = *root;
		*root = (*root)->right;
		(*root)->left = tmp;
		tmp->right = 0;
	}
	else if ((*root)->type == logical && (*root)->right->right != 0)
	{
		tmp = *root;
		*root = (*root)->right->right;
		(*root)->left = tmp;
		tmp->right->right = 0;
	}
	if ((*root)->right->right)
		balance_parse_tree(root);
}

int	make_basic_parse_tree_3(t_parse_tree *tree_tmp, \
	t_parse_tree *root, t_parse_list **head)
{
	if (make_paren_tree_node(tree_tmp, head) == 0)
	{
		free_parse_list(*head);
		free_parse_tree(root);
		return (0);
	}
	return (1);
}

void	make_basic_parse_tree_2(t_parse_tree **root)
{
	if (check_tree_syntax_error(*root) == 0)
	{
		free_parse_tree(*root);
		*root = 0;
		return ;
	}
	balance_parse_tree(root);
}

void	break_lst_link(t_parse_list **head)
{
	t_parse_list	*tmp;

	tmp = (*head)->next;
	(*head)->next = 0;
	(*head) = tmp;
}

void	make_args_tree_node(t_parse_tree *tree_tmp, t_parse_list **head)
{
	tree_tmp->type = organized_args;
	tree_tmp->lst = *head;
	while ((*head)->next != 0
		&& (*head)->next->token_type != logical
		&& (*head)->next->token_type != parenthesis)
		*head = (*head)->next;
	break_lst_link(head);
}
