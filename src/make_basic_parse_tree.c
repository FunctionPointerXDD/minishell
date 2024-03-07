/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_basic_parse_tree.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:46:49 by sihong            #+#    #+#             */
/*   Updated: 2024/02/12 15:46:59 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_logic_tree_node(t_parse_tree *tree_tmp, t_parse_list **head)
{
	t_parse_list	*tmp;

	tree_tmp->type = logical;
	tree_tmp->lst = *head;
	break_lst_link(head);
	if (check_blank(*head) == 1)
	{
		tmp = (*head)->next;
		free((*head)->s);
		if ((*head)->execve_args)
			free_split((*head)->execve_args);
		free(*head);
		*head = tmp;
	}
}

int	make_paren_tree_node_3(t_paren_stack **paren_top, t_parse_list **head)
{
	t_parse_list	*tmp;

	if (*paren_top != 0)
	{
		free_paren_stack(paren_top);
		return (0);
	}
	free_paren_stack(paren_top);
	break_lst_link(head);
	if (check_blank(*head) == 1)
	{
		tmp = (*head)->next;
		free((*head)->s);
		if ((*head)->execve_args)
			free_split((*head)->execve_args);
		free(*head);
		*head = tmp;
	}
	return (1);
}

void	make_paren_tree_node_2(t_parse_tree *tree_tmp, t_parse_list **head, \
								t_paren_stack **paren_top)
{
	tree_tmp->type = parenthesis;
	tree_tmp->lst = *head;
	*paren_top = new_paren_stack('(');
	*head = (*head)->next;
}

int	make_paren_tree_node(t_parse_tree *tree_tmp, t_parse_list **head)
{
	t_paren_stack	*paren_top;

	if ((*head)->s[0] == ')')
		return (0);
	make_paren_tree_node_2(tree_tmp, head, &paren_top);
	while (*head != 0)
	{
		if ((*head)->token_type == parenthesis)
		{
			push_paren_stack((*head)->s[0], &paren_top);
			if (paren_top->paren == ')' && paren_top->next->paren == '(')
			{
				pop_paren_stack(&paren_top);
				pop_paren_stack(&paren_top);
			}
			if (!paren_top)
				break ;
		}
		*head = (*head)->next;
	}
	if (make_paren_tree_node_3(&paren_top, head) == 0)
		return (0);
	return (1);
}

t_parse_tree	*make_basic_parse_tree(t_parse_list *head)
{
	t_parse_tree	*root;
	t_parse_tree	*tree_tmp;

	root = ft_calloc_adv(1, sizeof(t_parse_tree));
	tree_tmp = root;
	while (head != 0)
	{
		if (head->token_type == logical)
			make_logic_tree_node(tree_tmp, &head);
		else if (head->token_type == parenthesis)
		{
			if (make_basic_parse_tree_3(tree_tmp, root, &head) == 0)
				return (0);
		}
		else
			make_args_tree_node(tree_tmp, &head);
		if (head)
		{
			tree_tmp->right = ft_calloc_adv(1, sizeof(t_parse_tree));
			tree_tmp = tree_tmp->right;
		}
	}
	make_basic_parse_tree_2(&root);
	return (root);
}
