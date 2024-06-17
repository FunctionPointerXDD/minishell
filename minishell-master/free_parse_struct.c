/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:42:37 by sihong            #+#    #+#             */
/*   Updated: 2024/02/12 18:42:49 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parse_list(t_parse_list *head)
{
	t_parse_list	*tmp;

	if (head == 0)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->s)
			free(tmp->s);
		if (tmp->execve_args)
			free_split(tmp->execve_args);
		if (tmp->file_name)
			free(tmp->file_name);
		free(tmp);
	}
}

void	free_parse_tree(t_parse_tree *root)
{
	if (root == 0)
		return ;
	free_parse_tree(root->left);
	free_parse_tree(root->right);
	free_parse_list(root->lst);
	free(root);
}
