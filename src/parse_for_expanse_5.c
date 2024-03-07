/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_expanse_5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:58:49 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 21:14:44 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reformat_node(t_run_parse_info *info, t_run_parse_lst *start, char *res)
{
	t_run_parse_lst	*tmp;
	t_run_parse_lst	*new_node;

	tmp = start->next;
	while (tmp != info->tail && tmp->t_type != space)
	{
		tmp = tmp->prev;
		delete_node(info, tmp->next);
		tmp = tmp->next;
	}
	new_node = ft_calloc_adv(1, sizeof(t_run_parse_lst));
	new_node->token = res;
	new_node->t_type = wild_card;
	new_node->next = start->next;
	new_node->prev = start;
	start->next->prev = new_node;
	start->next = new_node;
}

int	apply_wild_card(t_run_parse_info *info, t_run_parse_lst *tmp)
{
	char			*tmp_string;
	char			*res;
	t_run_parse_lst	*start;

	res = 0;
	while (tmp != info->head && tmp->t_type != space)
		tmp = tmp->prev;
	start = tmp;
	tmp = tmp->next;
	while (tmp != info->tail && tmp->t_type != space)
	{
		tmp_string = res;
		res = ft_strjoin_adv(tmp_string, tmp->token);
		free(tmp_string);
		tmp = tmp->next;
	}
	tmp_string = res;
	expanse_s(&res);
	if (ft_strncmp(res, tmp_string, ft_strlen(tmp_string) + 1) == 0)
	{
		free(res);
		return (0);
	}
	reformat_node(info, start, res);
	return (1);
}

int	check_wildcard(t_run_parse_lst *tmp)
{
	char	*check;

	check = tmp->token;
	while (*check)
	{
		if (*check == '*')
		{
			tmp->t_type = wild_card;
			return (1);
		}
		check++;
	}
	return (0);
}

void	dispose_wildcard(t_run_parse_info *info)
{
	t_run_parse_lst	*tmp;
	t_run_parse_lst	*next_tmp;

	tmp = info->head->next;
	while (tmp != info->tail)
	{
		info_quote(info, tmp);
		if (tmp->t_type == words && !info->d_quote && !info->s_quote)
		{
			if (check_wildcard(tmp))
			{
				next_tmp = tmp;
				while (next_tmp != info->tail && next_tmp->t_type != space)
					next_tmp = next_tmp->next;
				if (apply_wild_card(info, tmp->next))
				{
					tmp = next_tmp;
					continue ;
				}
			}
		}
		tmp = tmp->next;
	}
}

t_run_parse_info	*parse_quote(t_run_parse_info *info)
{
	t_run_parse_lst	*tmp;

	tmp = info->head->next;
	while (tmp != info->tail)
	{
		if (tmp->t_type == p_s_quote || tmp->t_type == p_d_quote)
		{
			if ((tmp->next->t_type == p_s_quote) || \
				(tmp->next->t_type == p_d_quote))
			{
				free(tmp->token);
				tmp->token = ft_strdup_adv("");
				tmp->t_type = words;
			}
			else
			{
				tmp = tmp->prev;
				delete_node(info, tmp->next);
			}
		}
		tmp = tmp->next;
	}
	return (info);
}
