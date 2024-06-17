/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_flag_width.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:31:59 by sihong            #+#    #+#             */
/*   Updated: 2023/10/25 15:32:18 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_x_zero(char *input)
{
	int		check_zero;
	size_t	i;

	i = 0;
	check_zero = 0;
	while (input[i])
	{
		if (input[i] != '0')
			check_zero = 1;
		i++;
	}
	return (check_zero);
}

int	flag_hash(char **input, t_list_pt *cond)
{
	char	*temp;

	if (cond->flag.hash)
	{
		if ((cond->sign.x || cond->sign.upper_x)
			&& is_x_zero(*input))
		{
			temp = *input;
			*input = (char *)ft_calloc(ft_strlen(temp) + 3, sizeof(char));
			if (*input == 0)
			{
				free(temp);
				return (0);
			}
			(*input)[0] = '0';
			if (cond->sign.x)
				(*input)[1] = 'x';
			else if (cond->sign.upper_x)
				(*input)[1] = 'X';
			ft_strlcpy(&((*input)[2]), temp, ft_strlen(temp) + 1);
			free(temp);
		}
	}
	return (1);
}

int	flag_plus_space(char **input, t_list_pt *cond)
{
	char	*temp;

	if (cond->flag.plus || cond->flag.space)
	{
		if (cond->sign.d || cond->sign.i)
		{
			if ((*input)[0] != '-')
			{
				temp = *input;
				*input = (char *)ft_calloc(ft_strlen(temp) + 2, sizeof(char));
				if (*input == 0)
				{
					free(temp);
					return (0);
				}
				if (cond->flag.space)
					(*input)[0] = ' ';
				else if (cond->flag.plus)
					(*input)[0] = '+';
				ft_strlcpy(&((*input)[1]), temp, ft_strlen(temp) + 1);
				free(temp);
			}
		}
	}
	return (1);
}

void	form_flag_case_paste_at_right(char **input, t_list_pt *cond, char *temp)
{
	if (!cond->flag.minus)
	{
		if ((temp[0] == '+' || temp[0] == ' ' || temp[0] == '-')
			&& cond->flag.zero && (cond->sign.d || cond->sign.i
				|| cond->sign.u))
		{
			(*input)[0] = temp[0];
			ft_strlcpy(&((*input)[ft_strlen(*input) - ft_strlen(&temp[1])]),
				&temp[1], ft_strlen(&temp[1]) + 1);
		}
		else if ((temp[0] == '0' && (temp[1] == 'x' || temp[1] == 'X')
				&& (cond->sign.x || cond->sign.upper_x)) && cond->flag.hash
			&& cond->flag.zero)
		{
			(*input)[0] = temp[0];
			(*input)[1] = temp[1];
			ft_strlcpy(&((*input)[ft_strlen(*input) - ft_strlen(&temp[2])]),
				&temp[2], ft_strlen(&temp[2]) + 1);
		}
		else
		{
			ft_strlcpy(&((*input)[ft_strlen(*input) - ft_strlen(temp)]),
				temp, ft_strlen(temp) + 1);
		}
	}
}

char	*form_flag(char **input, t_list_pt *cond)
{
	char	*temp;

	if (input == 0 || *input == 0)
		return (0);
	if (!flag_plus_space(input, cond) || !flag_hash(input, cond))
		return (0);
	if (cond->flag.width > (int)ft_strlen(*input))
	{
		temp = *input;
		*input = (char *)ft_calloc(cond->flag.width + 1, sizeof(char));
		if (*input == 0)
		{
			free(temp);
			return (0);
		}
		if (cond->flag.zero)
			ft_memset(*input, '0', cond->flag.width);
		else
			ft_memset(*input, ' ', cond->flag.width);
		if (cond->flag.minus)
			ft_memcpy(*input, temp, ft_strlen(temp));
		form_flag_case_paste_at_right(input, cond, temp);
		free(temp);
	}
	return (*input);
}
