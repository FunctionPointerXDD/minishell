/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:08:10 by sihong            #+#    #+#             */
/*   Updated: 2024/02/12 14:08:13 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_parse_tree *root)
{
	int	i;
	t_parse_list	*tmp;

	if (root == 0)
		return ;
	print_tree(root->left);
	if (root->type == organized_args)
		printf("NODE TYPE : organized_args\n");
	else if (root->type == logical)
		printf("NODE TYPE : logical\n");
	printf("[\n");
	tmp = root->lst;
	while (root->lst)
	{
		printf("	LIST_NODE_INFO\n");
		if (root->lst->token_type == organized_args)
			printf("	TOKEN_TYPE : organized_args\n");
		else if (root->lst->token_type == pipex)
			printf("	TOKEN_TYPE : pipex\n");
		else if (root->lst->token_type == redirection)
			printf("	TOKEN_TYPE : redirection\n");
		else if (root->lst->token_type == logical)
			printf("	TOKEN_TYPE : logical\n");
		if (root->lst->file_name)
			printf("	FILE_NAME : %s\n", root->lst->file_name);
		printf("	STRING : %s\n", root->lst->s);
		i = 0;
		if (root->lst->execve_args)
		{
			while (root->lst->execve_args[i])
			{
				printf("	EXECVE ARGS[%d] : %s\n", i, root->lst->execve_args[i]);
				i++;
			}
		}
		printf("	+++\n");
		root->lst = root->lst->next;
	}
	root->lst = tmp;
	printf("]\n\n");
	printf("---\n\n");
	print_tree(root->right);
}

void	print_list(t_parse_list *head)
{
	while (head)
	{
		printf("lst->type : %d, lst-> : %s\n", head->token_type, head->s);
		head = head->next;
	}
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
	if (make_complete_parse_tree(&root) == 1)
	{
		write(2, "minishell : syntax error\n", 25);
		free_parse_tree(root);
		return (0);
	}
	return (root);
}
