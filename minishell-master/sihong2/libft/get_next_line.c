/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:33:50 by sihong            #+#    #+#             */
/*   Updated: 2023/10/17 13:43:28 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_data(t_list **head)
{
	t_list	*prev_nod;
	t_list	*now_nod;

	while ((*head) && (*head)->is_end != 0)
	{
		now_nod = *head;
		*head = (*head)->next;
		free(now_nod->buf);
		free(now_nod);
	}
	now_nod = *head;
	while (now_nod)
	{
		prev_nod = now_nod;
		now_nod = now_nod->next;
		if (now_nod == 0)
			return ;
		if (now_nod->is_end == 1)
		{
			prev_nod->next = now_nod->next;
			free(now_nod->buf);
			free(now_nod);
			now_nod = prev_nod;
		}
	}
}

void	*ft_calloc_cp(size_t count, size_t size)
{
	void	*result;
	char	*result_copy;
	size_t	i;

	result = malloc(size * count);
	if (result == 0)
		return (0);
	result_copy = (char *)result;
	i = 0;
	while (i < size * count)
		result_copy[i++] = 0;
	return (result);
}

char	*ft_substr_cp(char const *s, size_t start, size_t len, size_t buf_size)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	if (start > i)
		len = 0;
	else if (start + len > i)
		len = i - start;
	if (buf_size == 0)
		tmp = (char *)ft_calloc_cp(len + 1, sizeof(char));
	else
		tmp = (char *)ft_calloc_cp(buf_size, sizeof(char));
	if (tmp == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		tmp[i] = s[start + i];
		if (s[start + i] == 0)
			return (tmp);
		i++;
	}
	return (tmp);
}

int	is_head_null(t_list **head, int fd)
{
	t_list	*head_temp;

	if (head == 0)
		return (0);
	if (*head == 0)
	{
		*head = (t_list *)ft_calloc_cp(1, sizeof(t_list));
		if (*head == 0)
			return (0);
		(*head)->fd = fd;
		return (1);
	}
	head_temp = *head;
	while (head_temp->next && head_temp->fd != fd)
		head_temp = head_temp->next;
	if (head_temp->fd != fd)
	{
		head_temp->next = (t_list *)ft_calloc_cp(1, sizeof(t_list));
		if (head_temp->next == 0)
			return (0);
		(head_temp->next)->fd = fd;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	char			*result;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647 || fd < 0)
		return (0);
	if (is_head_null(&head, fd) == 0)
		return (0);
	result = read_file(head, fd);
	free_data(&head);
	if (result == 0)
		return (0);
	return (result);
}
