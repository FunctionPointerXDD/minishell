/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse_wild_card.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:18:36 by sihong            #+#    #+#             */
/*   Updated: 2024/02/15 13:19:02 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expanse_s(char **s)
{
	t_wild_key_lst	*wild_key_lst;
	char			*expansed_s;
	DIR				*dp;
	t_dirent		*dir_info;

	wild_key_lst = get_key_lst(*s);
	if (wild_key_lst == 0)
		return ;
	expansed_s = 0;
	dp = opendir_adv(".");
	dir_info = readdir(dp);
	while (dir_info)
	{
		if (dir_info->d_name[0] != '.' || (dir_info->d_name[0] == '.' \
			&& wild_key_lst->key && wild_key_lst->key[0] == '.'))
			get_expansed_s(wild_key_lst, dir_info->d_name, &expansed_s);
		dir_info = readdir(dp);
	}
	closedir(dp);
	free_wild_key_lst(wild_key_lst);
	if (expansed_s != 0)
	{
		free(*s);
		*s = expansed_s;
	}
}

void	expanse_wild_card(t_parse_list *head)
{
	int	i;

	while (head)
	{
		if (head->token_type == organized_args)
		{
			i = 0;
			while (head->execve_args[i])
			{
				expanse_s(&head->execve_args[i]);
				i += 1;
			}
		}
		head = head->next;
	}
}
