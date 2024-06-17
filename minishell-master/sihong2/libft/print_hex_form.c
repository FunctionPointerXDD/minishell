/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_form.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:36:51 by sihong            #+#    #+#             */
/*   Updated: 2023/10/25 15:37:02 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_hex_char(char *result, size_t num, int i, int is_upper)
{
	if (num == 0)
		result[i] = '0';
	while (num)
	{
		if (num % 16 >= 10)
		{
			if (is_upper)
				result[i] = num % 16 + ('A' - 10);
			else
				result[i] = num % 16 + ('a' - 10);
		}
		else
			result[i] = num % 16 + '0';
		num /= 16;
		i -= 1;
	}
}

size_t	find_hex_len(size_t num)
{
	size_t	i;

	i = 0;
	if (num == 0)
		i = 1;
	while (num)
	{
		num /= 16;
		i += 1;
	}
	return (i);
}

char	*print_hex_form(size_t num, int show_0x, int is_upper)
{
	size_t	i;
	char	*result;

	i = find_hex_len(num);
	if (show_0x)
		result = (char *)ft_calloc(i + 3, sizeof(char));
	else
		result = (char *)ft_calloc(i + 1, sizeof(char));
	if (result == 0)
		return (0);
	if (show_0x)
	{
		result[0] = '0';
		result[1] = 'x';
		i = i + 1;
	}
	else
		i = i - 1;
	put_hex_char(result, num, i, is_upper);
	return (result);
}
