/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_complete_parse_tree.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:47:08 by sihong            #+#    #+#             */
/*   Updated: 2024/02/13 10:47:20 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_complete_parse_tree_2(t_parse_tree **root)
{
	t_parse_list	*lst_tmp;
	t_parse_tree	*tree_tmp;

	lst_tmp = (*root)->lst;
	(*root)->lst = (*root)->lst->next;
	free(lst_tmp->s);
	free(lst_tmp);
	lst_tmp = (*root)->lst;
	while (lst_tmp->next->next)
		lst_tmp = lst_tmp->next;
	free(lst_tmp->next->s);
	free(lst_tmp->next);
	lst_tmp->next = 0;
	tree_tmp = make_basic_parse_tree((*root)->lst);
	(*root)->lst = 0;
	if (tree_tmp == 0)
		return (1);
	free_parse_tree(*root);
	*root = tree_tmp;
	return (0);
}

int	make_complete_parse_tree(t_parse_tree **root)
{
	if (*root == 0)
		return (0);
	if ((*root)->type == parenthesis
		&& (*root)->left == 0 && (*root)->right == 0)
	{
		if (make_complete_parse_tree_2(root) == 1)
			return (1);
	}
	if (make_complete_parse_tree(&(*root)->left)
		|| make_complete_parse_tree(&(*root)->right))
		return (1);
	return (0);
}
