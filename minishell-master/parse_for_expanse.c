/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_expanse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:20:12 by chansjeo          #+#    #+#             */
/*   Updated: 2024/02/29 18:56:41 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	list_print(t_run_parse_info *info)
{
	t_run_parse_lst *tmp;

	tmp = info->head->next;
	printf("=====list printing=====\n");
	while (tmp != info->tail)
	{
		if (tmp->token_type == words)
			printf("words");
		else if(tmp->token_type == var)
			printf("var");
		else if(tmp->token_type == p_double_quote)
			printf("double_quote");
		else if(tmp->token_type == p_single_quote)
			printf("single_quote");
		else if(tmp->token_type == space)
			printf("space");
		else if(tmp->token_type == wild_card)
			printf("wildcard");
		printf(": [%s]\n", tmp->token);
		tmp = tmp->next;
	}
	printf("=====list printing end=====\n");
}
*/

t_run_parse_info	*init_parse_info(void)
{
	t_run_parse_info	*info;

	info = ft_calloc_adv(1, sizeof(t_run_parse_info));
	info->head = ft_calloc_adv(1, sizeof(t_run_parse_lst));
	info->tail = ft_calloc_adv(1, sizeof(t_run_parse_lst));
	info->head->next = info->tail;
	info->tail->prev = info->head;
	info->size = 0;
	info->s_quote = 0;
	info->d_quote = 0;
	info->front_space = 0;
	info->rear_space = 0;
	return (info);
}

int insert_node(t_run_parse_info *info, char *str, int type)
{
	t_run_parse_lst* new_node;

	new_node = ft_calloc_adv(1, sizeof(t_run_parse_lst));
	new_node->token = str; 
	new_node->t_type = type;
	new_node->next = info->tail;
	new_node->prev = info->tail->prev;
	info->tail->prev->next = new_node;
	info->tail->prev = new_node;
	info->size += 1;
	return (0);
}

int	delete_node(t_run_parse_info *info, t_run_parse_lst *node)
{
	t_run_parse_lst	*cur;

	cur = node;		
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	free(cur->token);
	free(cur);
	info->size -= 1;
	return (0);
}

size_t ft_strcspn(t_run_parse_info *info, const char *str, char *reject)
{
	const char *p;

	p = str;
	while (*p != '\0')
	{
		if (ft_strchr(reject, *p))
		{
			if ((*p == '\'' && info->d_quote) ||
				(*p == '\"' && info->s_quote) ||
				(*p == '$' && info->s_quote))
			{
				p++;
				continue;
			}
			break;
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
			break;
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

void	strsep_to_list(t_run_parse_info* info, char *str)
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

void	insert_space_node(t_run_parse_info *info)
{
	char	*str;

	str = ft_strdup_adv(" ");
	insert_node(info, str, space);
}

t_run_parse_info	*parse_create(t_run_parse_info *info, char **argv)
{
	int i;

	i = 0;
	while (argv && argv[i])
	{
		strsep_to_list(info, argv[i]);
		if (argv[i + 1] != 0)
			insert_space_node(info);
		i++;
	}
	info->d_quote = 0;
	info->s_quote = 0;
	return (info);
}

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
 
t_run_parse_info *parse_var_expansion(t_run_parse_info *info, t_env_info *env_info)
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

void	reconnect_node(t_run_parse_lst *tmp, t_run_parse_lst *tmp_prev, char *buf)
{
	t_run_parse_lst	*new_node;
	t_run_parse_lst	*space_node;

	space_node = ft_calloc_adv(1, sizeof(t_run_parse_lst));
	space_node->token = ft_strdup_adv(" ");
	space_node->t_type = space;
	new_node = ft_calloc_adv(1, sizeof(t_run_parse_lst));
	new_node->token = ft_strdup_adv(buf);
	new_node->t_type = words;
	space_node->prev = tmp_prev;
	space_node->next = new_node;
	new_node->next = tmp;
	new_node->prev = space_node;
	tmp->prev = new_node;
	tmp_prev->next = space_node;
}

void	reconnect_space_node(t_run_parse_lst *tmp, t_run_parse_lst *tmp_prev)	
{
	t_run_parse_lst	*space_node;

	space_node = ft_calloc_adv(1, sizeof(t_run_parse_lst));
	space_node->token = ft_strdup_adv(" ");
	space_node->t_type = space;
	space_node->prev = tmp_prev;
	space_node->next = tmp;
	tmp->prev = space_node;
	tmp_prev->next = space_node;
}

void	split_to_list(t_run_parse_info *info, t_run_parse_lst *tmp, char **bufs)
{
	t_run_parse_lst	*tmp_prev;
	t_run_parse_lst	*tmp_tmp_prev;
	int				i;

	tmp_prev = tmp->prev->prev;
	tmp_tmp_prev = tmp_prev;
	delete_node(info, tmp->prev);
	i = 0;
	while (bufs && bufs[i])
	{
		reconnect_node(tmp, tmp_prev, bufs[i]);
		tmp_prev = tmp_prev->next->next;
		i++;
	}
	info->size += (i - 1) * 2;
	if (info->rear_space)
		reconnect_space_node(tmp, tmp_prev);
	if (!info->front_space)
		delete_node(info, tmp_tmp_prev->next);
	i = 0;
	while (bufs && bufs[i])
		free(bufs[i++]);
	free(bufs);
}

void	info_quote(t_run_parse_info *info, t_run_parse_lst *tmp)
{
	if (tmp->t_type == p_d_quote)
		info->d_quote = 1 - info->d_quote;
	else if (tmp->t_type == p_s_quote)
		info->s_quote = 1 - info->s_quote;
}

void	info_space(t_run_parse_info *info, t_run_parse_lst *tmp)
{
	char	*rear;

	rear = tmp->token;
	while (rear && *rear != 0)
		rear++;
	if (*(rear - 1) == ' ')
		info->rear_space = 1;
	if (*(tmp->token) == ' ')
		info->front_space = 1;
}

t_run_parse_info *parse_word_split(t_run_parse_info *info)
{
	t_run_parse_lst	*tmp;
	t_run_parse_lst *tmp_next;
	char			**bufs;

	tmp = info->head->next;
	while (tmp != info->tail)
	{
		info_quote(info, tmp);
		if (tmp->t_type == words && !info->d_quote && !info->s_quote)
		{
			bufs = ft_split_adv(tmp->token, ' ');			
			if (bufs)
			{
				info_space(info, tmp);
				tmp_next = tmp->next;
				split_to_list(info, tmp->next, bufs);
				tmp = tmp_next;
				info->rear_space = 0;
				info->front_space = 0;
				continue ;
			}
		}
		tmp = tmp->next;
	}
	return (info);
}

void	check_wildcard(t_run_parse_info *info)
{
	t_run_parse_lst	*tmp;
	char			*check;

	tmp = info->head->next;
	while (tmp != info->tail)
	{
		info_quote(info, tmp);
		if (tmp->t_type == words && !info->d_quote && !info->s_quote)
		{
			check = tmp->token;
			while (*check)
			{
				if (*check == '*')
				{
					tmp->t_type = wild_card;
					break ;
				}
				check++;
			}
		}
		tmp = tmp->next;
	}
}

t_run_parse_info *parse_quote(t_run_parse_info *info)
{
	t_run_parse_lst	*tmp;

	tmp = info->head->next;
	while (tmp != info->tail)	
	{
		if (tmp->t_type == p_s_quote || tmp->t_type == p_d_quote)
		{
			if ((tmp->next->t_type == p_s_quote) || (tmp->next->t_type == p_d_quote))
			{
				free(tmp->token);
				tmp->token = ft_strdup_adv("");
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

int	check_wild_token_type(t_run_parse_info *info, t_run_parse_lst *tmp)
{
	while (tmp != info->head)
	{
		if (tmp->t_type == wild_card)
			return (1);
		tmp = tmp->prev;
	}
	return (0);
}

char	**parse_to_char(t_run_parse_info *info)
{
	t_run_parse_lst	*tmp;
	char			**res;
	int				i;
	char			*tmp_string;

	res = make_char_frame(info);
	i = 0;
	tmp = info->head->next;
	while (tmp != info->tail)
	{
		while (tmp != info->tail && tmp->t_type != space)
		{
			tmp_string = res[i];
			res[i] = ft_strjoin_adv(tmp_string, tmp->token);
			free(tmp_string);
			tmp = tmp->next;
		}
		if (check_wild_token_type(info, tmp->prev))
			expanse_s(&res[i]);
		if (tmp == info->tail)
			break ;
		i++;
		tmp = tmp->next;
	}
	return (res);
}

void	clear_node(t_run_parse_info *info)
{
	t_run_parse_lst *tmp;
	t_run_parse_lst *delete;

	tmp = info->head->next;
	while (tmp != info->tail)
	{
		delete = tmp;
		tmp = tmp->next;
		free(delete->token);
		free(delete);
	}
	free(info->head);
	free(info->tail);
	free(info);
}

void	clear_old_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
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
		info = parse_word_split(info);
		check_wildcard(info);
		info = parse_quote(info);
		res = parse_to_char(info);
		clear_node(info);
		info = 0;
		clear_old_argv(argv);	
	}
	return (res);
}
