/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:34:18 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 20:06:15 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_here_doc(t_parse_list *lst, t_cmd_tool *cmd)
{
	t_parse_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->token_type == pipex)
			break ;
		if (ft_strncmp(tmp->s, "<<", 3) == 0)
			cmd->here_doc++;
		tmp = tmp->next;
	}
}

int	wait_proc(t_env_info *info)
{
	int	wstatus;

	wstatus = 0;
	while (wait(&wstatus) > 0)
		;
	if (WIFEXITED(wstatus))
		info->exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		info->exit_status = WTERMSIG(wstatus) + 128;
	return (0);
}

void	init_fd(t_cmd_tool *cmd)
{
	cmd->fd = -1;
	cmd->prev_fd = -1;
}
