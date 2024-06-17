/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperate_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:21:59 by sihong            #+#    #+#             */
/*   Updated: 2024/02/06 11:22:09 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_quote_syntax_error(char quote)
{
	if (quote == '\'')
	{
		write(2, "minishell: unexpected EOF while looking for matching `\'\'\n",
			57);
		write(2, "minishell: syntax error: unexpected end of file\n", 48);
	}
	else if (quote == '\"')
	{
		write(2, "minishell: unexpected EOF while looking for matching `\"\'\n",
			57);
		write(2, "minishell: syntax error: unexpected end of file\n", 48);
	}
}

int	make_quote_node(char *line, t_parse_list **tmp, int *anchor, int *i)
{
	char	quote;

	quote = line[*i];
	if (*i != 0)
	{
		substr_args(line, tmp, anchor, i);
		*anchor = *i;
	}
	*i += 1;
	while (line[*i] != 0 && line[*i] != quote)
		*i += 1;
	if (line[*i] == 0)
	{
		write_quote_syntax_error(quote);
		return (0);
	}
	else
	{
		(*tmp)->s = ft_substr_adv(line, *anchor, *i - *anchor + 1);
		(*tmp)->token_type = quote;
		(*tmp)->next = ft_calloc_adv(1, sizeof(t_parse_list));
		*tmp = (*tmp)->next;
		*anchor = *i + 1;
	}
	return (1);
}

void	substr_args(char *line, t_parse_list **tmp, int *anchor, int *i)
{
	(*tmp)->s = ft_substr_adv(line, *anchor, *i - *anchor);
	(*tmp)->token_type = args;
	(*tmp)->next = ft_calloc_adv(1, sizeof(t_parse_list));
	*tmp = (*tmp)->next;
}

t_parse_list	*seperate_quote(char *line)
{
	t_parse_list	*head;
	t_parse_list	*tmp;
	int				anchor;
	int				i;

	head = ft_calloc_adv(1, sizeof(t_parse_list));
	tmp = head;
	anchor = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			if (make_quote_node(line, &tmp, &anchor, &i) == 0)
			{
				free_parse_list(head);
				return (0);
			}
		}
		i += 1;
	}
	if (i != 0 && line[i - 1] != '\'' && line[i - 1] != '\"')
		substr_args(line, &tmp, &anchor, &i);
	return (head);
}
