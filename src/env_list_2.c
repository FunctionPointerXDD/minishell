/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:57:41 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 19:03:30 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* insert at tail */
int	insert_env(t_env_info *info, char *param)
{
	t_env_list	*new_node;

	new_node = ft_calloc_adv(1, sizeof(t_env_list));
	new_node->data = ft_strdup_adv(param);
	new_node->next = info->tail;
	new_node->prev = info->tail->prev;
	info->tail->prev->next = new_node;
	info->tail->prev = new_node;
	info->size += 1;
	return (0);
}

void	find_env_check_equal(char *equal1, char *equal2)
{
	if (equal1)
		*equal1 = '\0';
	if (equal2)
		*equal2 = '\0';
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
		find_env_check_equal(equal1, equal2);
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
	dummy->head = ft_calloc_adv(1, sizeof(t_env_list));
	dummy->tail = ft_calloc_adv(1, sizeof(t_env_list));
	dummy->head->next = dummy->tail;
	dummy->tail->prev = dummy->head;
	dummy->exit_status = 0;
	dummy->size = 0;
}
