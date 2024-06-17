/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:10:14 by chansjeo          #+#    #+#             */
/*   Updated: 2023/11/24 19:19:49 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_fd(char c, int fd)
{
	int	len;

	len = write(fd, &c, 1);
	if (len == -1)
		return (-1);
	return (len);
}

int	print_fmt(char ch, va_list arg, int fd)
{
	int	len;

	len = 0;
	if (ch == 'c')
		len = ft_putchar_fd(va_arg(arg, int), fd);
	else if (ch == 's')
		len = ft_putstr_fd(va_arg(arg, char *), fd);
	else if (ch == 'd' || ch == 'i')
		len = ft_putnbr_fd(va_arg(arg, int), fd);
	else if (ch == 'u')
		len = ft_putnbr_u_fd(va_arg(arg, unsigned int), fd);
	else if (ch == '%')
		len = ft_putchar_fd('%', fd);
	else if (ch == 'x' || ch == 'X')
		len = ft_puthex(va_arg(arg, unsigned int), ch, fd);
	else
		len = ft_puthex_p(va_arg(arg, unsigned long), ch, fd);
	return (len);
}

int	ft_vfprintf(int fd, const char *fmt, char ch, va_list arg)
{
	int				written;	
	int				len;

	written = 0;
	while (1)
	{
		ch = *fmt++;
		if (ch == '%')
		{
			ch = *fmt++;
			len = print_fmt(ch, arg, fd);
			if (len <= -1)
				return (-1);
			written += len;
		}
		else
		{
			if (ch == '\0')
				break ;
			if (write(1, &ch, 1) == -1)
				return (-1);
			written++;
		}
	}
	return (written);
}

int	ft_printf(const char *s, ...)
{
	int		ret;
	va_list	arg;

	va_start(arg, s);
	ret = ft_vfprintf(1, s, '\0', arg);
	va_end(arg);
	return (ret);
}
