/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:31:02 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 18:59:26 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* duplicate envp to list */
t_env_info	*make_env_list(t_env_info *info, char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		insert_env(info, envp[i++]);
	return (info);
}

char	*get_env_key(t_env_info *info, char *param)
{
	t_env_list	*tmp;
	char		*res;
	char		*equal;

	res = 0;
	tmp = find_env(info, param);
	if (tmp)
	{
		res = ft_strdup_adv(tmp->data);
		equal = ft_strchr(res, '=');
		if (equal)
			*equal = '\0';
	}
	return (res);
}

char	*get_env_value(t_env_info *info, char *param)
{
	t_env_list	*tmp;
	char		*res;
	char		*equal;

	res = 0;
	tmp = find_env(info, param);
	if (tmp)
	{
		equal = ft_strchr(tmp->data, '=');
		if (equal)
			res = ft_strdup_adv((equal + 1));
	}
	return (res);
}

char	**list_to_argv(t_env_info *info)
{
	char		**new_envp;	
	t_env_list	*tmp;
	int			i;

	new_envp = ft_calloc_adv(info->size + 1, sizeof(char *));
	i = 0;
	tmp = info->head->next;
	while (tmp != info->tail)
	{
		new_envp[i] = ft_calloc_adv(1, ft_strlen(tmp->data) + 1);
		ft_strlcpy(new_envp[i], tmp->data, ft_strlen(tmp->data) + 1);
		i++;
		tmp = tmp->next;
	}
	new_envp[i] = 0;
	return (new_envp);
}

t_env_info	*init_env(char **envp)
{
	t_env_info	*dummy;

	dummy = ft_calloc_adv(1, sizeof(t_env_info));
	init_info(dummy);
	dummy = make_env_list(dummy, envp);
	return (dummy);
}
