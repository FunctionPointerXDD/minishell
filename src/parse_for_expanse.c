/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_expanse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:20:12 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 21:23:24 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_replace(t_run_parse_lst *tmp, t_env_info *env_info)
{
	char	*replace;

	replace = 0;
	if (*(tmp->token) == '?')
		replace = ft_itoa(env_info->exit_status);
	else
		replace = get_env_value(env_info, tmp->token);
	return (replace);
}

t_run_parse_info	*parse_var_expansion(t_run_parse_info *info, \
					t_env_info *env_info)
{
	t_run_parse_lst	*tmp;
	char			*replace;

	tmp = info->head->next;
	while (tmp != info->tail)
	{
		if (tmp->t_type == var)
		{
			replace = get_replace(tmp, env_info);
			if (replace)
			{
				free(tmp->token);
				tmp->token = replace;
				tmp->t_type = words;
			}
			else
			{
				tmp = tmp->prev;
				delete_node(info, tmp->next);
			}
		}
		tmp = tmp->next;
	}
	return (info);
}

char	**make_char_frame(t_run_parse_info *info)
{
	t_run_parse_lst	*tmp;
	int				cnt;
	char			**res;

	cnt = 0;
	tmp = info->head->next;
	while (tmp != info->tail)
	{
		while (tmp != info->tail && tmp->t_type == space)
			tmp = tmp->next;
		if (tmp == info->tail)
			break ;
		while (tmp != info->tail && tmp->t_type != space)
			tmp = tmp->next;
		cnt++;
		if (tmp == info->tail)
			break ;
		tmp = tmp->next;
	}
	res = ft_calloc_adv(cnt + 2, sizeof(char *));
	return (res);
}

char	**parse_to_char(t_run_parse_info *info, int i)
{
	t_run_parse_lst	*tmp;
	char			**res;
	char			*tmp_string;

	res = make_char_frame(info);
	tmp = info->head->next;
	while (tmp != info->tail)
	{
		while (tmp != info->tail && tmp->t_type == space)
			tmp = tmp->next;
		while (tmp != info->tail && tmp->t_type != space)
		{
			tmp_string = res[i];
			res[i] = ft_strjoin_adv(tmp_string, tmp->token);
			free(tmp_string);
			tmp = tmp->next;
		}
		if (tmp == info->tail)
			break ;
		i++;
		tmp = tmp->next;
	}
	return (res);
}

char	**parse_for_expansion(char **argv, t_env_info *env_info)
{
	t_run_parse_info	*info;
	char				**res;

	res = 0;
	if (argv && *argv)
	{
		info = init_parse_info();
		info = parse_create(info, argv);
		info = parse_var_expansion(info, env_info);
		info = parse_word_split(info, words);
		dispose_wildcard(info);
		info = parse_word_split(info, wild_card);
		info = parse_quote(info);
		res = parse_to_char(info, 0);
		clear_node_and_argv(info, argv);
		info = 0;
	}
	return (res);
}
