/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:59:19 by chansjeo          #+#    #+#             */
/*   Updated: 2023/12/23 13:23:13 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_putchar_fd(char c, int fd);
int	ft_putnbr_fd(int n, int fd);
int	ft_putstr_fd(char *s, int fd);
int	ft_putnbr_u_fd(unsigned int n, int fd);
int	ft_puthex(unsigned int n, char ch, int fd);
int	ft_puthex_p(unsigned long n, char ch, int fd);
int	print_fmt(char ch, va_list arg, int fd);
int	ft_vfprintf(int fd, const char *fmt, char ch, va_list arg);
int	ft_printf(const char *s, ...);

#endif
