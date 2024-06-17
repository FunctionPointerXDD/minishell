/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:48 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/01 17:21:44 by chansjeo         ###   ########.fr       */
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

int	check_slash(char *param)
{
	while (param && *param)
	{
		if (*param == '/')
			return (1);
		param++;
	}
	return (0);
}

int	slash_cmd_check(t_cmd_tool *cmd, char *param)
{
	struct stat	sbuf;

	if (!check_slash(param))
		return (0);
	if (param && stat(param, &sbuf) == -1)
	{
		perror(param);
		return (1);
	}
	if (S_ISDIR(sbuf.st_mode))
	{
		cmd->error_code = 126;
		put_error(param, 2);
	}
	else
	{
		if (access(param, X_OK) == 0)
			cmd->path = ft_strdup(param);
		else
		{
			cmd->error_code = 126;
			put_error(param, 3);
		}
	}
	return (1);
}

int	dot_cmd_check(t_cmd_tool *cmd, char *param)
{
	char	*str;
	char	*slash;

	str = param;
	slash = ft_strrchr(str, '/');
	if (ft_strncmp(slash + 1, ".", 2) == 0)
	{
		ft_putstr_fd(".: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		cmd->error_code = 2;	
		return (1);
	}
	else if (ft_strncmp(slash + 1, "..", 3) == 0)
	{
		put_error("..", 1);
		cmd->error_code = 127;
		return (1);
	}
	return (0);
}

int	is_blank(char *param, t_cmd_tool *cmd)
{
	int	i;

	i = 0;
	if (*param == '\0')
	{
		cmd->error_code = 127;
		put_error(param, 1);
		return (1);
	}
	while (param && param[i])
	{
		if (param[i] != ' ')
			return (0);
		i++;
	}
	cmd->error_code = 127;
	put_error(param, 1);
	return (1);
}

void	cmd_check(t_cmd_tool *cmd, char *param, char **envp)
{
	char	**path_list;
	char	*path_line;
	int		i;

	i = 0;
	if (is_blank(param, cmd))
		return ;
	if (slash_cmd_check(cmd, param))
		return ;
	path_line = get_path_line(envp);
	path_list = path_parser(path_line, param);
	while (path_list && path_list[i])
	{
		if (dot_cmd_check(cmd, path_list[i]))
			return ;
		if (access(path_list[i], X_OK) == 0)
		{
			cmd->path = ft_strdup(path_list[i]);
			break ;
		}
		else
			cmd->path = 0;
		i++;
	}
	free_all(path_list, i, cmd, param);
}
