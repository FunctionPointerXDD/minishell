/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganize_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:42:43 by sihong            #+#    #+#             */
/*   Updated: 2024/03/06 16:05:25 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_filename_2(int *i, t_parse_list *head)
{
	char	**s_tmp;

	s_tmp = ft_calloc_adv(split_len(head->next->execve_args), \
			sizeof(char *));
	*i = 0;
	while (*i < split_len(head->next->execve_args) - 1)
	{
		s_tmp[*i] = head->next->execve_args[*i + 1];
		*i += 1;
	}
	free(head->next->execve_args);
	head->next->execve_args = s_tmp;
}

void	alloc_filename(t_parse_list *head)
{
	t_parse_list	*tmp;
	int				i;

	while (head)
	{
		if (head->token_type == redirection)
		{
			head->file_name = head->next->execve_args[0];
			if (split_len(head->next->execve_args) - 1 > 0)
				alloc_filename_2(&i, head);
			else
			{
				tmp = head->next->next;
				free(head->next->s);
				free(head->next->execve_args);
				free(head->next);
				head->next = tmp;
			}
		}
		head = head->next;
	}
}

void	organize_args_2(t_parse_list *head_tmp, t_parse_list **lst)
{
	char	*s_tmp;

	while (1)
	{
		if ((*lst)->token_type == single_quote \
			|| (*lst)->token_type == double_quote)
			quote_replace_space((*lst)->s);
		s_tmp = head_tmp->s;
		head_tmp->s = ft_strjoin_adv(head_tmp->s, (*lst)->s);
		if (s_tmp)
			free(s_tmp);
		if ((*lst)->next != 0 && ((*lst)->next->token_type == args \
			|| (*lst)->next->token_type == single_quote \
			|| (*lst)->next->token_type == double_quote))
			(*lst) = (*lst)->next;
		else
			break ;
	}
	head_tmp->execve_args = ft_split_adv(head_tmp->s, ' ');
	qoute_rollback_space(head_tmp->execve_args);
	head_tmp->token_type = organized_args;
}

t_parse_list	*organize_args(t_parse_list *lst)
{
	t_parse_list	*head;
	t_parse_list	*head_tmp;
	t_parse_list	*lst_tmp;

	head = ft_calloc_adv(1, sizeof(t_parse_list));
	head_tmp = head;
	lst_tmp = lst;
	while (lst)
	{
		if (lst->token_type == args || lst->token_type == single_quote \
			|| lst->token_type == double_quote)
			organize_args_2(head_tmp, &lst);
		else
		{
			head_tmp->s = ft_strdup_adv(lst->s);
			head_tmp->token_type = lst->token_type;
		}
		lst = lst->next;
		if (lst != 0)
			head_tmp->next = ft_calloc_adv(1, sizeof(t_parse_list));
		head_tmp = head_tmp->next;
	}
	free_parse_list(lst_tmp);
	return (head);
}

t_parse_list	*reorganize_args(t_parse_list *lst)
{
	t_parse_list	*head;
	t_parse_list	*tmp;

	rm_blank_after_pipex(lst);
	head = organize_args(lst);
	if (check_blank(head) == 1)
	{
		tmp = head->next;
		free(head->s);
		if (head->execve_args)
			free_split(head->execve_args);
		free(head);
		head = tmp;
	}
	alloc_filename(head);
	return (head);
}
