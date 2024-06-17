/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperate_others_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:57:17 by sihong            #+#    #+#             */
/*   Updated: 2024/02/07 17:57:21 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_paren_node(char *s, t_parse_list **lst2_tmp, int *i)
{
	if (s[*i] == '(' || s[*i] == ')')
	{
		(*lst2_tmp)->s = ft_substr_adv(s, *i, 1);
		(*lst2_tmp)->token_type = parenthesis;
	}
}

void	rm_none_node(t_parse_list *head)
{
	while (head->next->token_type != none)
		head = head->next;
	free(head->next);
	head->next = 0;
}
