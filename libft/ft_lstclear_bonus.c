/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:36:32 by chansjeo          #+#    #+#             */
/*   Updated: 2023/10/16 16:24:40 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*delete;

	tmp = *lst;
	if (lst == 0 || del == 0)
		return ;
	while (tmp != 0)
	{
		delete = tmp;
		tmp = tmp->next;
		del(delete->content);
		free(delete);
	}
	*lst = 0;
}
