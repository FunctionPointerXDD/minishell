/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:48:46 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 18:44:52 by chansjeo         ###   ########.fr       */
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

int	cmd_echo(char **arg)
{
	int	i;
	int	option;

	option = 0;
	i = 1;
	while (arg && arg[i])
	{
		if (!echo_option_check(arg[i]))
			break ;
		else
			option = 1;
		i++;
	}
	while (arg && arg[i])
	{
		ft_putstr_fd(arg[i++], 1);
		if (arg && arg[i])
			ft_putstr_fd(" ", 1);
	}
	if (!option)
		ft_putstr_fd("\n", 1);
	return (0);
}

void	cmd_export_2(t_env_info *info, char **arg)
{
	int		i;
	char	*val;
	char	*equal;

	i = 0;
	while (arg && arg[++i])
	{
		val = ft_strdup(arg[i]);
		equal = ft_strchr(val, '=');
		if ((equal != 0) && (equal != val))
			*equal = '\0';
		if (ft_isdigit(*val) || !is_valid(val))
		{
			printf("%s : not a valid identifier\n", arg[i]);
			info->exit_status = 1;
		}
		else
		{
			if (ft_strchr(arg[i], '='))
				delete_env(info, arg[i]);
			if (!find_env(info, arg[i]))
				insert_env(info, arg[i]);
		}
		free(val);
	}
}

int	cmd_export(t_env_info *info, char **arg)
{
	t_env_list	*tmp;
	char		*key;
	char		*value;

	if (arg[1] == NULL)
	{
		tmp = info->head->next;
		while (tmp != info->tail)
		{
			key = get_env_key(info, tmp->data);
			value = get_env_value(info, tmp->data);
			if (value)
				printf("declare -x %s=\"%s\"\n", key, value);
			else
				printf("declare -x %s\n", key);
			free(key);
			free(value);
			tmp = tmp->next;
		}
	}
	cmd_export_2(info, arg);
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
