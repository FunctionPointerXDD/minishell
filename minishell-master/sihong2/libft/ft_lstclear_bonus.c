/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:19:35 by sihong            #+#    #+#             */
/*   Updated: 2023/10/09 18:20:08 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*temp2;

	if (del == 0 || lst == 0 || *lst == 0)
		return ;
	temp = *lst;
	while (temp->next)
	{
		temp2 = temp;
		temp = temp->next;
		del(temp2->content);
		free(temp2);
	}
	del(temp->content);
	free(temp);
	*lst = 0;
}
