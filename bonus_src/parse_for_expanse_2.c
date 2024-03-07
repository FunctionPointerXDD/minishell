/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_expanse_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:53:21 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 21:01:43 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strcspn(t_run_parse_info *info, const char *str, char *reject)
{
	const char	*p;

	p = str;
	while (*p != '\0')
	{
		if (ft_strchr(reject, *p))
		{
			if ((*p == '\'' && info->d_quote) || \
				(*p == '\"' && info->s_quote) || \
				(*p == '$' && info->s_quote))
			{
				p++;
				continue ;
			}
			break ;
		}
		p++;
	}
	return (p - str);
}

void	insert_quote_node(t_run_parse_info *info, char *str)
{
	char	*buf;
	int		type;

	type = 0;
	if (*str == '\'' && !info->d_quote)
	{
		info->s_quote = 1 - info->s_quote;
		type = p_s_quote;
	}
	else if (*str == '\"' && !info->s_quote)
	{
		info->d_quote = 1 - info->d_quote;
		type = p_d_quote;
	}
	buf = ft_substr_adv(str, 0, 1);
	insert_node(info, buf, type);
}

int	var_len(char *tmp)
{
	int	len;

	len = 0;
	if (*tmp == '?')
		return (len + 1);
	if (ft_isdigit(*tmp))
		return (len);
	while (*tmp)
	{
		if (!ft_isalnum(*tmp) && *tmp != '_')
			break ;
		tmp++;
		len++;
	}
	return (len);
}

size_t	insert_var_node(t_run_parse_info *info, char *str)
{
	size_t	len;
	char	*tmp;
	char	*buf;

	len = 0;
	tmp = ++str;
	if (tmp)
	{
		len = var_len(tmp);
		if (!len)
			buf = ft_strdup_adv("$");
		else
			buf = ft_substr_adv(str, 0, len);
		if (info->s_quote || !len)
			insert_node(info, buf, words);
		else
			insert_node(info, buf, var);
	}
	return (len + 1);
}

void	strsep_to_list(t_run_parse_info *info, char *str)
{
	size_t	len;
	char	*buf;

	while (str && *str)
	{
		len = ft_strcspn(info, str, "$\"\'");
		if (!len)
		{
			if (*str != '$')
				insert_quote_node(info, str++);
			else
			{
				len = insert_var_node(info, str);
				str += len;
			}
		}
		else
		{
			buf = ft_substr_adv(str, 0, len);
			insert_node(info, buf, words);
			str += len;
		}
	}
}
