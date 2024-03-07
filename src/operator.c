/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:00:37 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 20:41:52 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	oper_pipex(t_cmd_tool *cmd)
{
	if (cmd->prev_fd != -1)
	{
		if (dup2(cmd->prev_fd, 0) < 0)
			perror("dup2_prev_fd");
	}
	if (cmd->pipe_fd[1] != -1)
	{
		if (dup2(cmd->pipe_fd[1], 1) < 0)
			perror("dup2_pipe_fd[1]");
	}
}

void	redir_to_file(t_parse_list *tmp, t_cmd_tool *cmd, int stdnum)
{
	if (cmd->fd < 0)
	{
		perror(tmp->file_name);
		if (!cmd->is_builtin)
			exit(1);
	}
	else
	{
		if (dup2(cmd->fd, stdnum) < 0)
			perror("dup2_fd : < ");
		close(cmd->fd);
		cmd->fd = -1;
	}
}

void	redir_to_here_doc(t_cmd_tool *cmd)
{
	cmd->fd = open(cmd->here_doc_file[cmd->here_doc++], O_RDONLY);
	if (cmd->fd < 0)
	{
		if (cmd->here_doc_cnt != 0)
			perror("here_doc open()");
		if (!cmd->is_builtin)
			exit(1);
	}
	else
	{
		if (dup2(cmd->fd, 0) < 0)
			perror("dup2_fd : << ");
		close(cmd->fd);
		cmd->fd = -1;
	}
}

void	oper_redir(t_parse_list *lst, t_cmd_tool *cmd)
{
	t_parse_list	*tmp;

	tmp = lst;
	while (tmp && tmp->token_type != pipex)
	{
		if (ft_strncmp(tmp->s, "<", 2) == 0)
		{
			cmd->fd = open(tmp->file_name, O_RDONLY);
			redir_to_file(tmp, cmd, 0);
		}
		else if (ft_strncmp(tmp->s, ">", 2) == 0)
		{
			cmd->fd = open(tmp->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			redir_to_file(tmp, cmd, 1);
		}
		else if (ft_strncmp(tmp->s, ">>", 3) == 0)
		{
			cmd->fd = open(tmp->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
			redir_to_file(tmp, cmd, 1);
		}
		else if (ft_strncmp(tmp->s, "<<", 3) == 0)
			redir_to_here_doc(cmd);
		tmp = tmp->next;
	}
}
