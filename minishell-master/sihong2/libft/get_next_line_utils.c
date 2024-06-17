/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:14:17 by sihong            #+#    #+#             */
/*   Updated: 2023/10/18 13:14:19 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_line(t_list *head, char **result, size_t i, int fd)
{
	int	func_returned;

	func_returned = read(fd, &head->buf[i], BUFFER_SIZE);
	if (func_returned == 0)
	{
		head->is_end = 1;
		if (head->store != i)
		{
			*result = ft_substr_cp(head->buf,
					head->store, i + 1 - head->store, 0);
			if (*result == 0)
				return (0);
			return (1);
		}
		else
			return (0);
	}
	if (func_returned == -1)
	{
		head->is_end = 1;
		return (0);
	}
	return (-1);
}

int	change_buf_size(size_t *buf_size, size_t *i, t_list *head)
{
	char	*buf_temp;

	if (*i + BUFFER_SIZE >= *buf_size)
	{
		if (*i + BUFFER_SIZE >= *buf_size)
			*buf_size *= 2;
		buf_temp = head->buf;
		head->buf = ft_substr_cp(buf_temp, head->store, *buf_size, *buf_size);
		free(buf_temp);
		if (head->buf == 0)
		{
			head->is_end = 1;
			return (0);
		}
		*i -= head->store;
		head->store = 0;
	}
	return (1);
}

int	end_with_nl(t_list *head, size_t buf_size, size_t *i, char **result)
{
	while (head->buf[*i] != '\n' && head->buf[*i] != 0 && *i < buf_size)
		(*i)++;
	if (*i < buf_size && head->buf[*i] == '\n')
	{
		*result = ft_substr_cp(head->buf, head->store, *i + 1 - head->store, 0);
		if (*result == 0)
		{
			head->is_end = 1;
			return (0);
		}
		head->store = *i + 1;
		return (1);
	}
	return (-1);
}

int	set_data(size_t *buf_size, size_t *i, t_list **head, int fd)
{
	*buf_size = 4096;
	*i = 1;
	while (*buf_size * *i < BUFFER_SIZE)
		(*i)++;
	*buf_size = *buf_size * *i;
	while ((*head)->fd != fd)
		*head = (*head)->next;
	while ((*head)->store + BUFFER_SIZE >= *buf_size)
		*buf_size *= 2;
	if ((*head)->buf == 0)
	{
		(*head)->buf = ft_calloc_cp(*buf_size, sizeof(char));
		if ((*head)->buf == 0)
		{
			(*head)->is_end = 1;
			return (0);
		}
		if (read(fd, (*head)->buf, BUFFER_SIZE) <= 0)
		{
			(*head)->is_end = 1;
			return (0);
		}
	}
	*i = (*head)->store;
	return (1);
}

char	*read_file(t_list *head, int fd)
{
	size_t	buf_size;
	size_t	i;
	int		func_returned;
	char	*result;

	if (set_data(&buf_size, &i, &head, fd) == 0)
		return (0);
	while (1)
	{
		func_returned = end_with_nl(head, buf_size, &i, &result);
		if (func_returned == 0)
			return (0);
		else if (func_returned == 1)
			return (result);
		if (i >= buf_size || (i < buf_size && head->buf[i] == 0))
		{
			if (change_buf_size(&buf_size, &i, head) == 0)
				return (0);
			func_returned = read_line(head, &result, i, fd);
			if (func_returned == 0)
				return (0);
			else if (func_returned == 1)
				return (result);
		}
	}
}
