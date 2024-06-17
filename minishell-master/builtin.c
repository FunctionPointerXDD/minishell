/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:48:46 by chansjeo          #+#    #+#             */
/*   Updated: 2024/02/29 18:45:01 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_option_check(char *option)
{
	int	i;

	if (ft_strncmp(option, "-n", 2) != 0)
		return (0);
	i = 1;
	while (option && option[i])
	{
		if (option[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int cmd_echo(char **arg)
{
	int i;
	int option;

	option = 0;
	i = 1;
	while (arg && arg[i])
	{
		if (!echo_option_check(arg[i]))
			break ;
		option = 1;
		i++;
	}
	while (arg && arg[i])
	{
		printf("%s", arg[i++]);
		if (arg && arg[i])
			printf(" ");
	}
	if (!option)
		printf("\n");
	return (0);
}

int	cmd_cd(t_env_info *info, char *path)
{
	struct	stat sbuf;	
	//char		*tmp;
	//char		buf[MAX_PATH + 1];
	/* current of PWD should be info of PWD*/
	(void)info;

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

int	cmd_pwd()
{
	char	*tmp;
	char	buf[MAX_PATH + 1];

	tmp = getcwd(buf, MAX_PATH);
	if (!tmp)
		perror("getcwd :");
	printf("%s\n", tmp);
	return (0);
}

/* upper lower alphabet, numeric, underbar
	 char *getenv(char *name) */
int	is_valid(char *param)
{
	int	i;

	i = 0;
	while (param && param[i])
	{
		if (!ft_isalnum(param[i]) && param[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	cmd_export(t_env_info *info, char **arg)
{
	int			i;
	t_env_list	*tmp;
	char		*val;
	char		*equal;
	char		*key;
	char		*value;
	
	if (arg[1] == NULL)
	{
		tmp = info->head->next;
		while (tmp != info->tail)
		{
			key = get_env_key(info, tmp->data);
			value = get_env_value(info, tmp->data);
			printf("declare -x %s=\"%s\"\n", key, value);
			free(key);
			free(value);
			tmp = tmp->next;
		}
	}
	i = 1;
	while (arg && arg[i])
	{
		val = ft_strdup(arg[i]);
		equal = ft_strchr(val, '=');
		if ((equal != 0) && (equal != val))
			*equal = '\0';
		if (ft_isdigit(*val) || !is_valid(val))
			printf("%s : not a valid identifier\n", arg[i]);
		else
		{
			if (ft_strchr(arg[i], '='))
				delete_env(info, arg[i]);
			if (!find_env(info, arg[i]))
				insert_env(info, arg[i]);
		}
		i++;
		free(val);
	}
	return (0);
}

int	cmd_unset(t_env_info *info, char **arg)
{
	int		i;
	char	*equal;	

	i = 1;
	while (arg && arg[i])
	{
		equal = ft_strchr(arg[i], '=');
		if (equal || ft_isdigit(arg[i][0]) || !is_valid(arg[i]))
		{
			printf("%s : not a valid identifier\n", arg[i]);
			info->exit_status = 1;
		}
		else
			delete_env(info, arg[i]);
		i++;
	}
	return (0);
}

int cmd_env(t_env_info *info)
{
	t_env_list *tmp;

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
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

int cmd_exit(char **arg, int exit_status)
{
	int cnt;

	cnt = 0;
	while (arg && arg[cnt])
		cnt++;
	if (cnt > 2)
	{
		printf("too many values\n");
		return (1);
	}
	else if (cnt == 2)
	{
		if (scan_digit(arg[1]))
			exit_status = (unsigned char)ft_atol(arg[1]);
		else
		{
			ft_putstr_fd(arg[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit_status = 255;
		}
	}
	printf("exit\n");
	exit(exit_status);
}
