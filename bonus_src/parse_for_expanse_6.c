/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_expanse_6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:19:02 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 21:20:27 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	info_quote(t_run_parse_info *info, t_run_parse_lst *tmp)
{
	if (tmp->t_type == p_d_quote)
		info->d_quote = 1 - info->d_quote;
	else if (tmp->t_type == p_s_quote)
		info->s_quote = 1 - info->s_quote;
}

void	clear_node_and_argv(t_run_parse_info *info, char **argv)
{
	t_run_parse_lst	*tmp;
	t_run_parse_lst	*delete;
	int				i;

	tmp = info->head->next;
	while (tmp != info->tail)
	{
		delete = tmp;
		tmp = tmp->next;
		free(delete->token);
		free(delete);
	}
	free(info->head);
	free(info->tail);
	free(info);
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}
