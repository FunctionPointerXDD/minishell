/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:00:37 by chansjeo          #+#    #+#             */
/*   Updated: 2024/06/13 22:07:18 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_tmpfile(char buf[])
{
	char	*digit;
	long	i;

	i = 0;
	ft_memset(buf, 0, 27);
	ft_strlcpy(buf, "/tmp/.pipex_tmp", 27);
	while (i < INT_MAX)
	{
		if (access(buf, F_OK) < 0)
			break ;
		digit = 0;
		digit = ft_itoa(i++);
		buf[15] = '\0';
		ft_strlcat(buf, digit, 27);
		free(digit);
	}
}

void	heredoc_sigint(int signum)
{
	(void)signum;
	g_signum = SIGINT;
	close(0);
}

int	here_doc_write(t_cmd_tool *cmd, char *delimiter)
{
	char	*tmp;
	int	stdin_tmp;

	stdin_tmp = dup(0);
	tmp = 0;
	signal(SIGINT, heredoc_sigint);
	while (1)
	{
		tmp = readline("> \001\033[s\002");
		if (tmp == 0 || ft_strncmp(tmp, delimiter, ft_strlen(delimiter) + 1) == 0)
			break ;
		write(cmd->fd, tmp, ft_strlen(tmp));
		write(cmd->fd, "\n", 1);
		free(tmp);
	}
	if (tmp == 0)
	{
		if (g_signum != SIGINT)
			write(1, "\033[u\033[B\033[A", 9);
		else
		{
			if (dup2(stdin_tmp, 0) < 0)
				perror("dup2");
			close(stdin_tmp);
			cmd->here_doc_cnt = 0;
			g_signum = 0;
			free(tmp);
			close(cmd->fd);
			return (-1);
		}
	}
	free(tmp);
	close(cmd->fd);
	return (0);
}

void	count_here_doc(t_parse_tree *root, t_cmd_tool *cmd)
{
	t_parse_list	*tmp;

	if (root == 0)
		return ;
	count_here_doc(root->left, cmd);
	tmp = root->lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->s, "<<", 3) == 0)
			cmd->here_doc_cnt++;
		tmp = tmp->next;
	}
	count_here_doc(root->right, cmd);	
}

void	create_here_doc_stack(t_cmd_tool *cmd)
{
	cmd->here_doc_file = ft_calloc_adv(cmd->here_doc_cnt + 1, sizeof(char *));
}

void	here_doc_init(t_parse_tree *root, t_cmd_tool *cmd)
{
	t_parse_list	*tmp_lst;
    char			*delimiter;
	char			tmp[27];

	if (root == 0 || cmd->here_doc_cnt == 0)
		return ;
	here_doc_init(root->left, cmd);
	tmp_lst = root->lst;
	while (tmp_lst)
	{
		if (ft_strncmp(tmp_lst->s, "<<", 3) == 0)
		{
			free(cmd->tmpfile);
			cmd->tmpfile = 0;
			delimiter = tmp_lst->file_name;
			ft_bzero(&tmp, 27);
			get_tmpfile(tmp);
			cmd->tmpfile = ft_strdup_adv(tmp);
			cmd->fd = open(cmd->tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd->fd < 0)
				perror("open error");
			if (here_doc_write(cmd, delimiter) < 0)
				break ;
			cmd->here_doc_file[cmd->here_doc++] = ft_strdup_adv(cmd->tmpfile);
		}
		tmp_lst = tmp_lst->next;
	}
	cmd->here_doc_file[cmd->here_doc_cnt] = 0;
	here_doc_init(root->right, cmd);
}

void    oper_pipex(t_env_info *info, t_parse_list *lst, t_cmd_tool *cmd)
{
	(void)info;
	(void)lst;

	//printf("cmd->prevfd = %d\n", cmd->prev_fd);
	if (cmd->prev_fd != -1)
	{
		if (dup2(cmd->prev_fd, 0) < 0)
			perror("dup2_prev_fd");
	}
	//printf("cmd->fd[1] = %d\n", cmd->pipe_fd[1]);
	if (cmd->pipe_fd[1] != -1)
	{
		if (dup2(cmd->pipe_fd[1], 1) < 0)
			perror("dup2_pipe_fd[1]");
	}

}

void	   oper_redir(t_env_info *info, t_parse_list *lst, t_cmd_tool *cmd)
{
    t_parse_list    *tmp;

	(void)info;
    tmp = lst;
    while (tmp && tmp->token_type != pipex)
	{
		if (ft_strncmp(tmp->s, "<", 2) == 0)
		{
			cmd->fd = open(tmp->file_name, O_RDONLY);
			if (cmd->fd < 0)
			{
				perror("open()");
				if (!cmd->is_builtin)
					exit(1);
			}
			else
			{
				if (dup2(cmd->fd, 0) < 0)
					perror("dup2_fd : < ");
				close(cmd->fd);
				cmd->fd = -1;
			}
		}
		else if (ft_strncmp(tmp->s, ">", 2) == 0)
        {
            cmd->fd = open(tmp->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (cmd->fd < 0)
			{
                perror("open()");
				if (!cmd->is_builtin)
					exit(1);
			}
			else
			{
				if (dup2(cmd->fd, 1) < 0)
					perror("dup2_fd : > ");
				close(cmd->fd);
				cmd->fd = -1;
			}
        }
        else if (ft_strncmp(tmp->s, ">>", 3) == 0)
        {
            cmd->fd = open(tmp->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
            if (cmd->fd < 0)
			{
				perror("open()");
				if (!cmd->is_builtin)
					exit(1);
			}
			else
			{
				if (dup2(cmd->fd, 1) < 0)
					perror("dup2_fd : >> ");
				close(cmd->fd);
				cmd->fd = -1;
			}
        }
        else if (ft_strncmp(tmp->s, "<<", 3) == 0)
        {
			cmd->fd = open(cmd->here_doc_file[cmd->here_doc++], O_RDONLY);
			if (cmd->fd < 0)
			{
				if (cmd->here_doc_cnt != 0)
					perror("open()");
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
        tmp = tmp->next;
	}
}

