/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:31:02 by chansjeo          #+#    #+#             */
/*   Updated: 2024/02/26 17:14:38 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* insert at tail */
int insert_env(t_env_info *info, char *param)
{
	t_env_list* new_node;

	new_node = ft_calloc(1, sizeof(t_env_list));
	new_node->data = ft_strdup(param);
	new_node->next = info->tail;
	new_node->prev = info->tail->prev;
	info->tail->prev->next = new_node;
	info->tail->prev = new_node;
	info->size += 1;
	return (0);
}

/* duplicate envp to list */
t_env_info	*make_env_list(t_env_info *info, char **envp)
{
	int	i;
	
	i = 0;
	while (envp && envp[i])
		insert_env(info, envp[i++]);
	return (info);
}

t_env_list	*find_env(t_env_info *info, char *key)
{
	t_env_list	*tmp;
	char		*buf1;
	char		*buf2;
	char		*equal1;
	char		*equal2;

	tmp = info->head->next;
	while (tmp != info->tail)
	{
		buf1 = ft_strdup_adv(tmp->data);
		buf2 = ft_strdup_adv(key);
		equal1 = ft_strchr(buf1, '=');	
		equal2 = ft_strchr(buf2, '=');	
		if (equal1)
			*equal1 = '\0';
		if (equal2)
			*equal2 = '\0';
		if (ft_strncmp(buf1, buf2, ft_strlen(buf1) + 1) == 0)
		{
			free(buf1);
			free(buf2);
			return (tmp);
		}
		tmp = tmp->next;
		free(buf1);
		free(buf2);
	}
	return (0);
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

int	delete_env(t_env_info *info, char *param)
{
	t_env_list	*node;

	node = find_env(info, param);
	if (!node)
		return (1);
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node->data);
	free(node);
	info->size -= 1;
	return (0);
}

void	init_info(t_env_info *dummy)
{
	dummy->head = ft_calloc(1, sizeof(t_env_list));
	dummy->tail = ft_calloc(1, sizeof(t_env_list));
	dummy->head->next = dummy->tail;
	dummy->tail->prev = dummy->head;
	dummy->exit_status = 0;
	dummy->size = 0;
}

/* For envp of execve( , , envp) */
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

	dummy = ft_calloc(1, sizeof(t_env_info));
	init_info(dummy);
	dummy = make_env_list(dummy, envp);
	return (dummy);
}
