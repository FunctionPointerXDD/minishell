/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:56:47 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 16:58:21 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error(char *param, int code)
{
	if (code == 1)
	{
		ft_putstr_fd(param, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (code == 2)
	{
		ft_putstr_fd(param, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	else if (code == 3)
	{
		ft_putstr_fd(param, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

char	**path_parser(char *path_line, char *param)
{
	char	**path_arr;
	char	*tmp;
	int		i;

	if (!path_line)
		return (0);
	path_arr = ft_split(path_line, ':');
	i = 0;
	while (path_arr && path_arr[i])
	{
		tmp = path_arr[i];
		path_arr[i++] = gnl_strjoin(tmp, "/");
		free(tmp);
	}
	i = 0;
	while (path_arr && path_arr[i])
	{
		tmp = path_arr[i];
		path_arr[i++] = gnl_strjoin(tmp, param);
		free(tmp);
	}
	return (path_arr);
}

char	*get_path_line(char **envp)
{
	char	*path_line;

	path_line = NULL;
	while (envp && *envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path_line = *envp + 5;
			break ;
		}
		envp++;
	}
	return (path_line);
}

void	free_all(char **path_list, int cnt, t_cmd_tool *cmd, char *param)
{
	int	i;

	i = 0;
	if (!path_list)
	{
		cmd->error_code = 127;
		put_error(param, 1);
	}
	else if (!path_list[cnt])
	{
		cmd->error_code = 127;
		put_error(param, 1);
		while (path_list && path_list[i])
			free(path_list[i++]);
		free(path_list);
	}
	else
	{
		while (path_list && path_list[i])
			free(path_list[i++]);
		free(path_list);
	}
}

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' \
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}
