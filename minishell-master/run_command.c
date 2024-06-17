/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:56:42 by chansjeo          #+#    #+#             */
/*   Updated: 2024/05/24 18:53:11 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	all_close(t_cmd_tool *cmd)
{
	close(cmd->fd);
	close(cmd->pipe_fd[0]);
	close(cmd->pipe_fd[1]);
	close(cmd->prev_fd);
}

char	**count_execve_args(t_parse_list *tmp)
{
	char			**res;
	int				cnt;
	int				i;
	
	i = 0;
	cnt = 0;
	while (tmp)
	{
		if (tmp->token_type == pipex)
			break;
		if (tmp->token_type == organized_args)
		{
			while (tmp->execve_args[i++])
				cnt++;
		}
		tmp = tmp->next;
	}
	if (!cnt)
		return (0);
	res = ft_calloc_adv(cnt + 1, sizeof(char *));
	return (res);
}

char	**join_args(t_parse_list *lst)
{
	char			**res;
	int				i;
	int				j;
	t_parse_list	*tmp;
	
	tmp = lst;
	res = count_execve_args(tmp);
	i = 0;
	while (tmp)
	{
		if (tmp->token_type == pipex)
			break;
		if (tmp->token_type == organized_args)
		{
			j = 0;
			while (tmp->execve_args[j])
				res[i++] = ft_strdup_adv(tmp->execve_args[j++]);
		}
		tmp = tmp->next;
	}
	if (res)
		res[i] = 0;
	return (res);
}


int	is_builtin(char **arg)
{
	if (ft_strncmp("env", arg[0], 4) == 0)
		return (1);
	else if (ft_strncmp("export", arg[0], 7) == 0)
		return (1);
	else if (ft_strncmp("unset", arg[0], 6) == 0)
		return (1);
	else if (ft_strncmp("pwd", arg[0], 4) == 0)
		return (1);
	else if (ft_strncmp("cd", arg[0], 3) == 0)
		return (1);
	else if (ft_strncmp("echo", arg[0], 5) == 0)
		return (1);
	else if (ft_strncmp("exit", arg[0], 5) == 0)
		return (1);
	return (0);
}

t_parse_list	*check_pipe(t_parse_list *lst)
{
	while (lst)
	{
		if (lst->token_type == pipex)
			return (lst);
		lst = lst->next;
	}
	return (0);
}


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
		cmd_cd(info, arg[1]);
	else if (ft_strncmp("echo", arg[0], 5) == 0)
		cmd_echo(arg);
	else if (ft_strncmp("exit", arg[0], 5) == 0)
		cmd_exit(arg, info->exit_status);
	else
		return (0);
	return (1);
}

void	push_command(t_env_info *info, t_cmd_tool *cmd)
{
	if (exec_builtin(info, cmd->execve_argv))
	{
		all_close(cmd);
		exit(0);
	}
	else
	{
		all_close(cmd);
		execve(cmd->path, cmd->execve_argv, cmd->envp);
		exit(cmd->error_code);
	}
}

void	sigquit_handler(int signum)
{
	(void)signum;
	write(1, "Quit: 3\n", 8);
}

void	exec_child(t_env_info *info, t_parse_list *lst, t_cmd_tool *cmd)
{
	signal(SIGQUIT, sigquit_handler);
	cmd->pid = fork();
	if (cmd->pid > 0)
		return ;
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
			oper_pipex(info, lst, cmd);
			oper_redir(info, lst, cmd);
			all_close(cmd);
			exit(cmd->error_code);
		}
		cmd_check(cmd, cmd->execve_argv[0], cmd->envp);
		oper_pipex(info, lst, cmd);
		oper_redir(info, lst, cmd);
		push_command(info, cmd);
	}
}

void	exec_cmd_at_builtin(t_env_info *info, t_parse_list *lst, t_cmd_tool *cmd)
{
	int	stdin_tmp;
	int	stdout_tmp;

	cmd->is_builtin = 1;
	stdin_tmp = dup(0);
	stdout_tmp = dup(1);
	oper_redir(info, lst, cmd);
	exec_builtin(info, cmd->execve_argv);
	if (dup2(stdin_tmp, 0) < 0)
		perror("dup2()");
	close(stdin_tmp);
	if (dup2(stdout_tmp, 1) < 0)
		perror("dup2()");
	close(stdout_tmp);
}

void	update_here_doc(t_parse_list *lst, t_cmd_tool *cmd)	
{
	t_parse_list *tmp;

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
}

void	last_running(t_env_info *info, t_parse_list *tmp, t_cmd_tool *cmd)
{
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	cmd->execve_argv = join_args(tmp);
	cmd->execve_argv = parse_for_expansion(cmd->execve_argv, info);
	exec_child(info, tmp, cmd);
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
}

/* all cmd -> fork, then exec */
void exec_cmd_with_pipe(t_env_info *info, t_parse_list *lst, t_cmd_tool *cmd)
{
	t_parse_list *pipe_ofs;
	t_parse_list *tmp;

	tmp = lst;
	while (tmp)
	{
		pipe_ofs = check_pipe(lst->next);
		if (pipe_ofs)
		{
			if (pipe(cmd->pipe_fd))
			{
				perror("pipe()");
				return;
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

int	wait_proc(t_env_info *info)
{
	int wstatus;

	wstatus = 0;
	while (wait(&wstatus) > 0)
		;
	if (WIFEXITED(wstatus))
		info->exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		info->exit_status = WTERMSIG(wstatus) + 128;
	return (0);
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

void	init_fd(t_cmd_tool *cmd)
{
	cmd->fd = -1;
	cmd->prev_fd = -1;
}

/* ||, && 분기로 나뉨 */
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
		wait_proc(info);
	}
	run_command(info, root->right, cmd);
}
