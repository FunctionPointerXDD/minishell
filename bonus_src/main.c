/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:06:09 by sihong            #+#    #+#             */
/*   Updated: 2024/03/06 20:04:02 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dispose_here_doc(t_parse_tree *root, t_cmd_tool *cmd)
{
	count_here_doc(root, cmd);
	if (cmd->here_doc_cnt)
	{
		create_here_doc_stack(cmd);
		here_doc_init(root, cmd);
		free(cmd->tmpfile);
		cmd->here_doc = 0;
	}
}

void	init_cmd_tool(t_cmd_tool *cmd)
{
	ft_bzero(cmd, sizeof(t_cmd_tool));
	cmd->fd = -1;
	cmd->prev_fd = -1;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
}

void	unlink_here_doc_file(t_cmd_tool *cmd)
{
	int	i;

	i = 0;
	if (cmd->here_doc_cnt)
	{
		cmd->here_doc_cnt -= 1;
		while (i <= cmd->here_doc_cnt)
		{
			unlink(cmd->here_doc_file[i]);
			free(cmd->here_doc_file[i]);
			i++;
		}
		free(cmd->here_doc_file);
		cmd->here_doc_file = 0;
	}
}

void	exec_line(char *line, t_env_info *env_info)
{
	t_parse_tree	*root;
	t_cmd_tool		cmd;

	if (*line)
	{
		rl_on_new_line_adv();
		add_history(line);
		root = parse_line(line);
		if (!root)
			env_info->exit_status = 258;
		init_cmd_tool(&cmd);
		dispose_here_doc(root, &cmd);
		if (root && root->lst && cmd.escape != 1)
			run_command(env_info, root, &cmd);
		env_info->escape = 0;
		free_parse_tree(root);
		unlink_here_doc_file(&cmd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_env_info		*env_info;
	int				exit_status_tmp;	

	(void)argc;
	(void)argv;
	env_info = init_env(envp);
	rl_catch_signals = 0;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
		line = readline("minishell$ \001\033[s\002");
		if (g_signum == 1 && env_info->exit_status != 1)
			env_info->exit_status = 1;
		g_signum = 0;
		if (!line)
			break ;
		exec_line(line, env_info);
		free(line);
	}
	printf("\033[u\033[B\033[Aexit\n");
	exit_status_tmp = env_info->exit_status;
	free_all_env(env_info);
	return (exit_status_tmp);
}
