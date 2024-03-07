/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:48 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 16:58:14 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_blank(char *param)
{
	int	i;

	i = 0;
	if (*param == '\0')
		return (1);
	while (param && param[i])
	{
		if (!ft_isspace(param[i]))
			return (0);
		i++;
	}
	return (1);
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

void	filtering2(t_cmd_tool *cmd, char *param)
{
	if (access(param, X_OK) == 0)
		cmd->path = ft_strdup(param);
	else
	{
		cmd->error_code = 126;
		put_error(param, 3);
	}
}

int	filtering_cmd(t_cmd_tool *cmd, char *param)
{
	struct stat	sbuf;

	if (is_blank(param))
		return (-1);
	if (stat(param, &sbuf) == -1)
	{
		if (check_slash(param))
		{
			perror(param);
			cmd->error_code = 127;
			return (-1);
		}
		return (1);
	}
	if (S_ISDIR(sbuf.st_mode))
	{
		cmd->error_code = 126;
		put_error(param, 2);
	}
	filtering2(cmd, param);
	return (-1);
}

void	cmd_check(t_cmd_tool *cmd, char *param, char **envp)
{
	char	**path_list;
	char	*path_line;
	int		i;

	i = 0;
	if (filtering_cmd(cmd, param) < 0)
		return ;
	path_line = get_path_line(envp);
	path_list = path_parser(path_line, param);
	while (path_list && path_list[i])
	{
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
