/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:32:05 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/07 12:45:12 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_cd(char *path)
{
	struct stat	sbuf;	

	if (path && stat(path, &sbuf) == -1)
	{
		perror(path);
		return (1);
	}
	if (S_ISDIR(sbuf.st_mode))
	{
		if (chdir(path) == -1)
		{
			perror(path);
			return (1);
		}
	}
	else if (S_ISREG(sbuf.st_mode))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
		return (1);
	}
	return (0);
}

int	cmd_pwd(void)
{
	char	*tmp;
	char	buf[MAX_PATH + 1];

	tmp = getcwd(buf, MAX_PATH);
	if (!tmp)
		perror("getcwd");
	else
		printf("%s\n", tmp);
	return (0);
}

int	cmd_env(t_env_info *info)
{
	t_env_list	*tmp;

	tmp = info->head->next;
	while (tmp != info->tail)
	{
		if (ft_strchr(tmp->data, '='))
			printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
	return (0);
}

int	scan_digit(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > 20)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	cmd_exit(char **arg, int exit_status)
{
	int	cnt;

	cnt = 0;
	while (arg && arg[cnt])
		cnt++;
	if (cnt > 2)
	{
		printf("too many values\n");
		exit(-1);
	}
	else if (cnt == 2)
	{
		if (scan_digit(arg[1]))
			exit_status = ft_atol(arg[1]);
		else
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd(arg[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(-1);
		}
	}
	printf("exit\n");
	exit(exit_status);
}
