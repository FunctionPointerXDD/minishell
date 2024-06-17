/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_conditions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:33:38 by sihong            #+#    #+#             */
/*   Updated: 2023/10/25 13:34:07 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_error(t_list_pt *cond)
{
	if (cond->flag.plus && cond->flag.space)
		cond->flag.space = 0;
	if (!cond->sign.percent_sign
		&& (cond->flag.zero && cond->flag.precision))
		cond->flag.zero = 0;
	if (cond->flag.minus && cond->flag.zero)
		cond->flag.zero = 0;
}

int	check_sign(const char *format, t_list_pt *cond, size_t *i)
{
	if (format[*i] == 'c')
		cond->sign.c = 1;
	else if (format[*i] == 'd')
		cond->sign.d = 1;
	else if (format[*i] == 'i')
		cond->sign.i = 1;
	else if (format[*i] == 'p')
		cond->sign.p = 1;
	else if (format[*i] == '%')
		cond->sign.percent_sign = 1;
	else if (format[*i] == 's')
		cond->sign.s = 1;
	else if (format[*i] == 'u')
		cond->sign.u = 1;
	else if (format[*i] == 'X')
		cond->sign.upper_x = 1;
	else if (format[*i] == 'x')
		cond->sign.x = 1;
	else
		return (0);
	return (1);
}

void	check_precision(const char *format, t_list_pt *cond, size_t *i)
{
	if (format[*i] == '.')
	{
		cond->flag.precision = 1;
		(*i) += 1;
		while (format[*i] >= '0' && format[*i] <= '9')
		{
			cond->flag.precision_len = cond->flag.precision_len * 10
				+ (format[*i] - '0');
			(*i) += 1;
		}
	}
}

void	check_flag_width(const char *format, t_list_pt *cond, size_t *i)
{
	while (format[*i] == '-' || format[*i] == '0' || format[*i] == '#'
		|| format[*i] == ' ' || format[*i] == '+')
	{
		if (format[*i] == '-')
			cond->flag.minus = 1;
		if (format[*i] == '0')
			cond->flag.zero = 1;
		if (format[*i] == '#')
			cond->flag.hash = 1;
		if (format[*i] == ' ')
			cond->flag.space = 1;
		if (format[*i] == '+')
			cond->flag.plus = 1;
		(*i) += 1;
	}
	while (format[*i] >= '0' && format[*i] <= '9')
	{
		cond->flag.width = cond->flag.width * 10 + (format[*i] - '0');
		(*i) += 1;
	}
}

void	set_list_zero(t_list_pt *cond)
{
	cond->sign.c = 0;
	cond->sign.d = 0;
	cond->sign.i = 0;
	cond->sign.p = 0;
	cond->sign.percent_sign = 0;
	cond->sign.s = 0;
	cond->sign.u = 0;
	cond->sign.upper_x = 0;
	cond->sign.x = 0;
	cond->flag.hash = 0;
	cond->flag.minus = 0;
	cond->flag.plus = 0;
	cond->flag.precision = 0;
	cond->flag.precision_len = 0;
	cond->flag.space = 0;
	cond->flag.width = 0;
	cond->flag.zero = 0;
}
