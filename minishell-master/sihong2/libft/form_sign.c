/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_sign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:55:40 by sihong            #+#    #+#             */
/*   Updated: 2023/10/25 13:55:50 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	form_sign_char_s(t_list_pt *cond, va_list *arg_point, char **result)
{
	char	*s_temp;
	size_t	i;

	if (cond->sign.s)
	{
		s_temp = va_arg(*arg_point, char *);
		if (s_temp == 0)
			s_temp = "(null)";
		*result = (char *)ft_calloc(ft_strlen(s_temp) + 1, sizeof(char));
		if (*result == 0)
			return (0);
		i = -1;
		while (s_temp[++i])
			(*result)[i] = s_temp[i];
	}
	return (1);
}

int	form_sign_char(t_list_pt *cond, va_list *arg_point, char **result)
{
	if (cond->sign.c || cond->sign.percent_sign)
	{
		*result = (char *)ft_calloc(2, sizeof(char));
		if (*result == 0)
			return (0);
		if (cond->sign.c)
			(*result)[0] = va_arg(*arg_point, int);
		else if (cond->sign.percent_sign)
			(*result)[0] = '%';
	}
	if (form_sign_char_s(cond, arg_point, result) == 0)
		return (0);
	return (1);
}

int	form_sign_hex(t_list_pt *cond, va_list *arg_point, char **result)
{
	if (cond->sign.upper_x)
	{
		*result = print_hex_form((size_t)va_arg(*arg_point, unsigned int),
				0, 1);
		if (*result == 0)
			return (0);
	}
	if (cond->sign.x)
	{
		*result = print_hex_form((size_t)va_arg(*arg_point, unsigned int),
				0, 0);
		if (*result == 0)
			return (0);
	}
	if (cond->sign.p)
	{
		*result = print_hex_form((size_t)va_arg(*arg_point, void *), 1, 0);
		if (*result == 0)
			return (0);
	}
	return (1);
}

int	form_sign_dec(t_list_pt *cond, va_list *arg_point, char **result)
{
	if (cond->sign.d || cond->sign.i)
	{
		*result = ft_itoa(va_arg(*arg_point, int));
		if (*result == 0)
			return (0);
	}
	if (cond->sign.u)
	{
		*result = ft_uitoa(va_arg(*arg_point, unsigned int));
		if (*result == 0)
			return (0);
	}
	return (1);
}

char	*form_sign(t_list_pt *cond, va_list *arg_point)
{
	char	*result;

	if (!form_sign_dec(cond, arg_point, &result)
		|| !form_sign_hex(cond, arg_point, &result)
		|| !form_sign_char(cond, arg_point, &result))
		return (0);
	form_precision(cond, &result);
	return (result);
}
