/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_percent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:30:53 by sihong            #+#    #+#             */
/*   Updated: 2023/10/25 13:31:14 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*form_percent(const char *format, size_t *i, va_list *arg_pointer
	, int *is_c_null)
{
	t_list_pt	cond;
	char		*temp;

	set_list_zero(&cond);
	(*i) += 1;
	check_flag_width(format, &cond, i);
	check_precision(format, &cond, i);
	if (check_sign(format, &cond, i) == 0)
		return (0);
	check_error(&cond);
	temp = form_sign(&cond, arg_pointer);
	if (temp == 0)
		return (0);
	if (cond.sign.c && temp[0] == 0)
	{
		*is_c_null = 1;
		temp[0] = 127;
	}
	return (form_flag(&temp, &cond));
}
