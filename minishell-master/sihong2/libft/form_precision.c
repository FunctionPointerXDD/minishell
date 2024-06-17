/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_precision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:30:11 by sihong            #+#    #+#             */
/*   Updated: 2023/10/25 15:30:29 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	form_precision_string(t_list_pt *cond, char **result)
{
	char	*temp;

	if (cond->sign.s && cond->flag.precision_len < (int)ft_strlen(*result))
	{
		temp = *result;
		*result = (char *)ft_calloc(cond->flag.precision_len + 1,
				sizeof(char));
		if (*result == 0)
		{
			free(temp);
			return (0);
		}
		ft_strlcpy(*result, temp, cond->flag.precision_len + 1);
		free(temp);
	}
	return (1);
}

int	form_precision_case_value_zero(t_list_pt *cond, char **result)
{
	if (cond->flag.precision && (((*result)[0] == '0' && (*result)[1] == 0)
		|| ((*result)[0] == '0' && (*result)[1] == 'x' && (*result)[2] == 0)
		|| ((*result)[0] == '0' && (*result)[1] == 'X' && (*result)[2] == 0)))
	{
		free(*result);
		*result = (char *)ft_calloc(1, sizeof(char));
		if (*result == 0)
			return (0);
	}
	return (1);
}

int	form_precision_case_new_form(t_list_pt *cond, char **result, char *temp)
{
	temp = *result;
	if (temp[0] == '-')
		cond->flag.precision_len += 1;
		*result = (char *)ft_calloc(cond->flag.precision_len + 1,
			sizeof(char));
	if (*result == 0)
	{
		free(temp);
		return (0);
	}
	ft_memset(*result, '0', cond->flag.precision_len);
	if (temp[0] == '-')
	{
		(*result)[0] = temp[0];
		ft_strlcpy(&((*result)[ft_strlen(*result) - ft_strlen(&temp[1])]),
			&temp[1], ft_strlen(&temp[1]) + 1);
	}
	else
	{
		ft_strlcpy(&((*result)[ft_strlen(*result) - ft_strlen(temp)]),
			temp, ft_strlen(temp) + 1);
	}
	free(temp);
	return (1);
}

char	*form_precision(t_list_pt *cond, char **result)
{
	char	*temp;

	temp = 0;
	if (cond->flag.precision)
	{
		if (form_precision_string(cond, result) == 0)
			return (0);
		if (cond->sign.d || cond->sign.i || cond->sign.u || cond->sign.x
			|| cond->sign.upper_x)
		{
			if (form_precision_case_value_zero(cond, result) == 0)
				return (0);
			if (cond->flag.precision_len >= (int)ft_strlen(*result))
			{
				if (form_precision_case_new_form(cond, result, temp) == 0)
					return (0);
			}
		}
	}
	return (*result);
}
