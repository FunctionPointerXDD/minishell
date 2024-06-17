/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:07:53 by chansjeo          #+#    #+#             */
/*   Updated: 2023/10/17 20:07:56 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	create_list(t_list **head, t_list *lst, void *(*f)(void *))
{
	void	*item;
	t_list	*node;
	t_list	*tmp;

	tmp = lst;
	while (tmp != 0)
	{
		item = f(tmp->content);
		if (item == 0)
			return (0);
		node = ft_lstnew(item);
		if (node == 0)
		{
			free(item);
			return (0);
		}
		ft_lstadd_back(head, node);
		tmp = tmp->next;
	}
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	int		ret;

	if (f == 0 || del == 0)
		return (0);
	head = 0;
	ret = create_list(&head, lst, f);
	if (ret == 0)
	{
		ft_lstclear(&head, del);
		return (0);
	}
	return (head);
}
