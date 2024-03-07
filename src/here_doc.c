/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:39:03 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 20:49:34 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_tmpfile(char buf[])
{
	char	*digit;
	long	i;

	i = 0;
	ft_memset(buf, 0, 28);
	ft_strlcpy(buf, "/tmp/.pipex_tmp", 28);
	while (i < INT_MAX)
	{
		if (access(buf, F_OK) < 0)
			break ;
		ft_memset(buf, 0, 28);
		ft_strlcpy(buf, "/tmp/.pipex_tmp", 28);
		digit = 0;
		digit = ft_itoa(i++);
		buf[15] = '\0';
		ft_strlcat(buf, digit, 28);
		free(digit);
	}
}

void	read_here_doc(t_cmd_tool *cmd, char **tmp, char *delimiter)
{
	while (1)
	{
		*tmp = readline("> \001\033[s\002");
		if (*tmp == 0 || \
			ft_strncmp(*tmp, delimiter, ft_strlen(delimiter) + 1) == 0)
			break ;
		write(cmd->fd, *tmp, ft_strlen(*tmp));
		write(cmd->fd, "\n", 1);
		free(*tmp);
	}
}

int	here_doc_write(t_cmd_tool *cmd, char *delimiter)
{
	char	*tmp;
	int		stdin_tmp;

	stdin_tmp = dup(0);
	tmp = 0;
	signal(SIGINT, heredoc_sigint);
	read_here_doc(cmd, &tmp, delimiter);
	if (tmp == 0)
	{
		if (g_signum != SIGINT)
			write(1, "\033[u\033[B\033[A", 9);
		else
		{
			if (dup2(stdin_tmp, 0) < 0)
				perror("dup2");
			close(stdin_tmp);
			cmd->escape = 1;
			g_signum = 1;
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
