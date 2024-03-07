/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_expanse_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:57:13 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 21:13:21 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reconnect_node(t_run_parse_lst *tmp, \
		t_run_parse_lst *tmp_prev, char *buf)
{
	t_run_parse_lst	*new_node;
	t_run_parse_lst	*space_node;

	space_node = ft_calloc_adv(1, sizeof(t_run_parse_lst));
	space_node->token = ft_strdup_adv(" ");
	space_node->t_type = space;
	new_node = ft_calloc_adv(1, sizeof(t_run_parse_lst));
	new_node->token = ft_strdup_adv(buf);
	new_node->t_type = words;
	space_node->prev = tmp_prev;
	space_node->next = new_node;
	new_node->next = tmp;
	new_node->prev = space_node;
	tmp->prev = new_node;
	tmp_prev->next = space_node;
}

void	reconnect_space_node(t_run_parse_lst *tmp, t_run_parse_lst *tmp_prev)
{
	t_run_parse_lst	*space_node;

	space_node = ft_calloc_adv(1, sizeof(t_run_parse_lst));
	space_node->token = ft_strdup_adv(" ");
	space_node->t_type = space;
	space_node->prev = tmp_prev;
	space_node->next = tmp;
	tmp->prev = space_node;
	tmp_prev->next = space_node;
}

void	split_to_list(t_run_parse_info *info, t_run_parse_lst *tmp, char **bufs)
{
	t_run_parse_lst	*tmp_prev;
	t_run_parse_lst	*tmp_tmp_prev;
	int				i;

	tmp_prev = tmp->prev->prev;
	tmp_tmp_prev = tmp_prev;
	delete_node(info, tmp->prev);
	i = 0;
	while (bufs && bufs[i])
	{
		reconnect_node(tmp, tmp_prev, bufs[i]);
		tmp_prev = tmp_prev->next->next;
		i++;
	}
	info->size += (i - 1) * 2;
	if (info->rear_space)
		reconnect_space_node(tmp, tmp_prev);
	if (!info->front_space)
		delete_node(info, tmp_tmp_prev->next);
	i = 0;
	while (bufs && bufs[i])
		free(bufs[i++]);
	free(bufs);
}

void	info_space(t_run_parse_info *info, t_run_parse_lst *tmp)
{
	char	*rear;

	rear = tmp->token;
	while (rear && *rear != 0)
		rear++;
	if (*(rear - 1) == ' ')
		info->rear_space = 1;
	if (*(tmp->token) == ' ')
		info->front_space = 1;
}

t_run_parse_info	*parse_word_split(t_run_parse_info *info, int type)
{
	t_run_parse_lst	*tmp;
	t_run_parse_lst	*tmp_next;
	char			**bufs;

	tmp = info->head->next;
	while (tmp != info->tail)
	{
		info_quote(info, tmp);
		if ((int)tmp->t_type == type && !info->d_quote && !info->s_quote)
		{
			bufs = ft_split_adv(tmp->token, ' ');
			if (bufs)
			{
				info_space(info, tmp);
				tmp_next = tmp->next;
				split_to_list(info, tmp->next, bufs);
				tmp = tmp_next;
				info->rear_space = 0;
				info->front_space = 0;
				continue ;
			}
		}
		tmp = tmp->next;
	}
	return (info);
}
