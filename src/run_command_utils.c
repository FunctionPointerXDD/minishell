/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:25:59 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 20:06:07 by chansjeo         ###   ########.fr       */
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
	char	**res;
	int		cnt;
	int		i;

	i = 0;
	cnt = 0;
	while (tmp)
	{
		if (tmp->token_type == pipex)
			break ;
		if (tmp->token_type == organized_args)
		{
			i = 0;
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
			break ;
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
