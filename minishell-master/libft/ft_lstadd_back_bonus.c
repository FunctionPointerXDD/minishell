/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:55:20 by chansjeo          #+#    #+#             */
/*   Updated: 2023/10/23 16:33:44 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tail;

	tail = *lst;
	if (new == 0)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{
		while (tail->next != 0)
			tail = tail->next;
		tail->next = new;
	}
}
