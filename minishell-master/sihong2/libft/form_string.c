/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:25:38 by sihong            #+#    #+#             */
/*   Updated: 2023/10/25 13:26:03 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	resize_buf(char **storage, size_t *buf_size)
{
	char	*temp;

	temp = *storage;
	*buf_size *= 2;
	*storage = (char *)ft_calloc(*buf_size, sizeof(char));
	if (*storage == 0)
	{
		free(temp);
		return (0);
	}
	ft_strlcpy((char *)*storage, temp, *buf_size);
	free(temp);
	return (1);
}

void	check_c_null(char **storage, t_i_list *i_list, int is_c_null)
{
	if ((*storage)[i_list->s_i] == 127 && is_c_null)
		(*storage)[i_list->s_i] = 0;
	i_list->s_i += 1;
}

int	when_return_percent_sign(const char *format, char **storage,
	va_list *arg_pointer, t_i_list *i_list)
{
	int		is_c_null;
	char	*temp;
	size_t	paste_end;

	if (format[i_list->i] == '%')
	{
		is_c_null = 0;
		temp = form_percent(format, &(i_list->i), arg_pointer, &is_c_null);
		if (temp == 0)
			return (0);
		while (ft_strlen(*storage) + ft_strlen(temp) + 1 >= i_list->buffer_size)
		{	
			if (resize_buf(storage, &i_list->buffer_size) == 0)
				return (0);
		}
		ft_strlcpy(&((*storage)[i_list->s_i]), temp, ft_strlen(temp) + 1);
		paste_end = i_list->s_i + ft_strlen(temp);
		while (i_list->s_i < paste_end)
			check_c_null(storage, i_list, is_c_null);
		i_list->s_i -= 1;
		free(temp);
	}
	return (1);
}

int	form_string(const char *format, char **storage, size_t buf_size,
	va_list *arg_pointer)
{
	t_i_list	i_list;

	i_list.i = 0;
	i_list.s_i = 0;
	i_list.buffer_size = buf_size;
	while (format[i_list.i])
	{
		if (i_list.s_i >= i_list.buffer_size)
		{
			if (resize_buf(storage, &i_list.buffer_size) == 0)
				return (ERROR);
		}
		(*storage)[i_list.s_i] = format[i_list.i];
		if (when_return_percent_sign(format, storage, arg_pointer, &i_list)
			== 0)
			return (ERROR);
		i_list.i += 1;
		i_list.s_i += 1;
	}
	return (i_list.s_i);
}
