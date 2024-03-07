/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:56:42 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 17:41:42 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	last_running(t_env_info *info, t_parse_list *tmp, t_cmd_tool *cmd)
{
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	cmd->execve_argv = join_args(tmp);
	cmd->execve_argv = parse_for_expansion(cmd->execve_argv, info);
	exec_child(info, tmp, cmd);
	free_split(cmd->execve_argv);
}

void	general_running(t_env_info *info, t_parse_list *tmp, t_cmd_tool *cmd)
{
	cmd->execve_argv = join_args(tmp);
	cmd->execve_argv = parse_for_expansion(cmd->execve_argv, info);
	exec_child(info, tmp, cmd);
	close(cmd->prev_fd);
	close(cmd->pipe_fd[1]);
	cmd->prev_fd = cmd->pipe_fd[0];
	if (cmd->here_doc_cnt)
		update_here_doc(tmp, cmd);
	free_split(cmd->execve_argv);
}

/* all cmd -> fork, then exec */
void	exec_cmd_with_pipe(t_env_info *info, t_parse_list *lst, t_cmd_tool *cmd)
{
	t_parse_list	*pipe_ofs;
	t_parse_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		pipe_ofs = check_pipe(lst->next);
		if (pipe_ofs)
		{
			if (pipe(cmd->pipe_fd))
			{
				perror("pipe()");
				return ;
			}
			lst = pipe_ofs;
		}
		else
		{
			last_running(info, tmp, cmd);
			break ;
		}
		general_running(info, tmp, cmd);
		tmp = pipe_ofs->next;
	}
	all_close(cmd);
}

void	select_run(t_parse_list *lst, t_env_info *info)
{
	if (ft_strncmp(lst->s, "||", 3) == 0)
	{
		if (info->exit_status)
			info->escape = 0;
		else
			info->escape = 1;
	}
	else
	{
		if (info->exit_status)
			info->escape = 1;
		else
			info->escape = 0;
	}
}

void	run_command(t_env_info *info, t_parse_tree *root, t_cmd_tool *cmd)
{
	if (root == 0 || info->escape == 1)
		return ;
	run_command(info, root->left, cmd);
	if (root->lst->token_type == logical)
		select_run(root->lst, info);
	else
	{
		if (check_pipe(root->lst))
		{
			init_fd(cmd);
			exec_cmd_with_pipe(info, root->lst, cmd);
		}
		else
			exec_cmd(info, root->lst, cmd);
		if (!cmd->is_builtin)
			wait_proc(info);
	}
	run_command(info, root->right, cmd);
}
