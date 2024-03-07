/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_expanse_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:56:51 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 21:08:53 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_run_parse_info	*init_parse_info(void)
{
	t_run_parse_info	*info;

	info = ft_calloc_adv(1, sizeof(t_run_parse_info));
	info->head = ft_calloc_adv(1, sizeof(t_run_parse_lst));
	info->tail = ft_calloc_adv(1, sizeof(t_run_parse_lst));
	info->head->next = info->tail;
	info->tail->prev = info->head;
	info->size = 0;
	info->s_quote = 0;
	info->d_quote = 0;
	info->front_space = 0;
	info->rear_space = 0;
	return (info);
}

int	insert_node(t_run_parse_info *info, char *str, int type)
{
	t_run_parse_lst	*new_node;

	new_node = ft_calloc_adv(1, sizeof(t_run_parse_lst));
	new_node->token = str;
	new_node->t_type = type;
	new_node->next = info->tail;
	new_node->prev = info->tail->prev;
	info->tail->prev->next = new_node;
	info->tail->prev = new_node;
	info->size += 1;
	return (0);
}

int	delete_node(t_run_parse_info *info, t_run_parse_lst *node)
{
	t_run_parse_lst	*cur;

	cur = node;
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	free(cur->token);
	free(cur);
	info->size -= 1;
	return (0);
}

void	insert_space_node(t_run_parse_info *info)
{
	char	*str;

	str = ft_strdup_adv(" ");
	insert_node(info, str, space);
}

t_run_parse_info	*parse_create(t_run_parse_info *info, char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		strsep_to_list(info, argv[i]);
		if (argv[i + 1] != 0)
			insert_space_node(info);
		i++;
	}
	info->d_quote = 0;
	info->s_quote = 0;
	return (info);
}
