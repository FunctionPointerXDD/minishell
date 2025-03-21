/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:40:22 by chansjeo          #+#    #+#             */
/*   Updated: 2024/10/15 15:42:48 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_env_info *info, char **arg)
{
	if (ft_strncmp("env", arg[0], 4) == 0)
		cmd_env(info);
	else if (ft_strncmp("export", arg[0], 7) == 0)
		cmd_export(info, arg);
	else if (ft_strncmp("unset", arg[0], 6) == 0)
		cmd_unset(info, arg);
	else if (ft_strncmp("pwd", arg[0], 4) == 0)
		cmd_pwd();
	else if (ft_strncmp("cd", arg[0], 3) == 0)
		info->exit_status = cmd_cd(arg[1]);
	else if (ft_strncmp("echo", arg[0], 5) == 0)
		info->exit_status = cmd_echo(arg);
	else if (ft_strncmp("exit", arg[0], 5) == 0)
		cmd_exit(arg, info->exit_status);
	else
		return (0);
	return (1);
}

void	push_command(t_env_info *info, t_cmd_tool *cmd)
{
	if (is_builtin(cmd->execve_argv))
	{
		exec_builtin(info, cmd->execve_argv);
		all_close(cmd);
		exit(info->exit_status);
	}
	else
	{
		all_close(cmd);
		execve(cmd->path, cmd->execve_argv, cmd->envp);
		info->exit_status = cmd->error_code;
		exit(info->exit_status);
	}
}

void	exec_child(t_env_info *info, t_parse_list *lst, t_cmd_tool *cmd)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	if (cmd->fork_cnt++ > 500)
	{
		printf("too many fork()\n");
		exit(1);
	}
	cmd->pid = fork();
	if (cmd->pid > 0)
	{
		if (info->last_pid == 1)
			info->last_pid = cmd->pid;
		return ;
	}
	if (cmd->pid < 0)
	{
		perror("fork()");
		exit(1);
	}
	if (cmd->pid == 0)
	{
		cmd->envp = list_to_argv(info);
		if (!cmd->execve_argv)
		{
			all_close(cmd);
			exit(cmd->error_code);
		}
		/*
		if (!is_builtin(cmd->execve_argv))
		{
			oper_pipex(cmd);
			oper_redir(lst, cmd);
		}
		*/
		oper_pipex(cmd);
		oper_redir(lst, cmd);
		cmd_check(cmd, cmd->execve_argv[0], cmd->envp);
		push_command(info, cmd);
	}
}

/**
 * dup() --> std in/out backup!
 * dup2() --> std in/out restore!
*/
void	exec_cmd_at_builtin(t_env_info *info, \
		t_parse_list *lst, t_cmd_tool *cmd)
{
	int	stdin_tmp;
	int	stdout_tmp;

	cmd->is_builtin = 1;
	stdin_tmp = dup(0);
	stdout_tmp = dup(1);
	oper_redir(lst, cmd);
	exec_builtin(info, cmd->execve_argv);
	if (dup2(stdin_tmp, 0) < 0)
		perror("dup2()");
	close(stdin_tmp);
	if (dup2(stdout_tmp, 1) < 0)
		perror("dup2()");
	close(stdout_tmp);
}

/* no_pipe, builtin cmd -> not fork, then exec,
 * others cmd => fork, then exec			 */
void	exec_cmd(t_env_info *info, t_parse_list *lst, t_cmd_tool *cmd)
{
	t_parse_list	*tmp;

	tmp = lst;
	cmd->execve_argv = join_args(tmp);
	cmd->execve_argv = parse_for_expansion(cmd->execve_argv, info);
	if (cmd->execve_argv && cmd->execve_argv[0] && is_builtin(cmd->execve_argv))
		exec_cmd_at_builtin(info, lst, cmd);
	else
	{
		exec_child(info, tmp, cmd);
		update_here_doc(tmp, cmd);
	}
	all_close(cmd);
	free_split(cmd->execve_argv);
}

