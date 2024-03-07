/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse_wild_card_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:12:51 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 19:15:27 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_key_len(char *s, int start, int end)
{
	int		i;
	int		len;
	char	quote;

	i = start;
	len = 0;
	while (i < end)
	{
		while (s[i] == '\"' || s[i] == '\'')
		{
			quote = s[i];
			i += 1;
			while (s[i] != quote)
			{
				len += 1;
				i += 1;
			}
			i += 1;
		}
		if (i >= end)
			break ;
		len += 1;
		i += 1;
	}
	return (len);
}
