/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:20:24 by sihong            #+#    #+#             */
/*   Updated: 2023/10/25 13:20:46 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	char	*storage;
	int		func_returned;

	if (format == 0)
		return (ERROR);
	storage = (char *)ft_calloc(4096, sizeof(char));
	if (storage == 0)
		return (ERROR);
	va_start(ap, format);
	func_returned = form_string(format, &storage, 4096, &ap);
	if (func_returned != ERROR)
	{
		if (write(1, storage, func_returned) == -1)
		{
			free(storage);
			va_end(ap);
			return (ERROR);
		}
	}
	free(storage);
	va_end(ap);
	return (func_returned);
}
