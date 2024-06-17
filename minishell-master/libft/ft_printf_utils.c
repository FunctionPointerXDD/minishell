/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:22:32 by chansjeo          #+#    #+#             */
/*   Updated: 2023/12/14 20:18:33 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_fd(int n, int fd)
{
	int		mod;
	int		len;
	long	num;

	len = 0;
	num = n;
	if (n < 0)
	{
		if (write(fd, "-", 1) == -1)
			return (-1);
		num = -num;
	}
	if (num >= 10)
	{
		len += ft_putnbr_fd(num / 10, fd);
		if (len <= -1)
			return (-1);
	}
	mod = num % 10 + '0';
	if (write(fd, &mod, 1) == -1)
		return (-1);
	return (len + 1 + (n < 0));
}

int	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (!s)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	len = 0;
	while (s && *s++)
		len++;
	s -= len + 1;
	if (write(fd, s, len) == -1)
		return (-1);
	return (len);
}

int	ft_putnbr_u_fd(unsigned int n, int fd)
{
	unsigned char	mod;
	int				len;

	len = 0;
	if (n >= 10)
	{
		len += ft_putnbr_u_fd(n / 10, fd);
		if (len <= -1)
			return (-1);
	}
	mod = n % 10 + '0';
	if (write(fd, &mod, 1) == -1)
		return (-1);
	return (len + 1);
}

int	ft_puthex(unsigned int n, char ch, int fd)
{
	unsigned char	mod;
	int				len;
	const char		*hex;
	const char		*hex_up;

	hex = "0123456789abcdef";
	hex_up = "0123456789ABCDEF";
	len = 0;
	if (n >= 16)
	{
		len += ft_puthex(n / 16, ch, fd);
		if (len == -1)
			return (-1);
	}
	if (ch == 'X')
		mod = hex_up[n % 16];
	else
		mod = hex[n % 16];
	if (write(fd, &mod, 1) == -1)
		return (-1);
	return (len + 1);
}

int	ft_puthex_p(unsigned long n, char ch, int fd)
{
	unsigned char	mod;
	int				len;
	const char		*hex;

	len = 0;
	hex = "0123456789abcdef";
	if (n < 16)
	{
		if (write(fd, "0x", 2) == -1)
			return (-1);
		len += 2;
	}
	if (n >= 16)
	{
		len += ft_puthex_p(n / 16, ch, fd);
		if (len <= -1)
			return (-1);
	}
	mod = hex[n % 16];
	if (write(fd, &mod, 1) == -1)
		return (-1);
	return (len + 1);
}
