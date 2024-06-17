/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paren_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:46:42 by sihong            #+#    #+#             */
/*   Updated: 2024/02/12 17:46:46 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_paren_stack	*new_paren_stack(char paren)
{
	t_paren_stack	*top;

	top = ft_calloc_adv(1, sizeof(t_paren_stack));
	top->paren = paren;
	return (top);
}

void	push_paren_stack(char paren, t_paren_stack **top)
{
	t_paren_stack	*tmp;

	tmp = new_paren_stack(paren);
	tmp->next = *top;
	*top = tmp;
}

void	pop_paren_stack(t_paren_stack **top)
{
	t_paren_stack	*tmp;

	tmp = *top;
	*top = (*top)->next;
	free(tmp);
}

void	free_paren_stack(t_paren_stack **top)
{
	while (*top)
		pop_paren_stack(top);
}
