/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:11:18 by sihong            #+#    #+#             */
/*   Updated: 2023/10/09 19:11:35 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	put_data(t_list *lst, t_list *temp, t_list *result,
	void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp2;

	while (lst->next)
	{
		lst = lst->next;
		temp->next = (t_list *)malloc(sizeof(t_list));
		if (temp->next == 0)
		{
			while (result->next)
			{
				temp2 = result;
				del(result->content);
				result = result->next;
				free(temp2);
			}
			del(result->content);
			free(result);
			return (1);
		}
		temp = temp->next;
		temp->content = f(lst->content);
		temp->next = 0;
	}
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*result;

	if (lst == 0 || f == 0 || del == 0)
		return (0);
	temp = (t_list *)malloc(sizeof(t_list));
	if (temp == 0)
		return (0);
	temp->content = f(lst->content);
	temp->next = 0;
	result = temp;
	if (put_data(lst, temp, result, f, del))
		return (0);
	return (result);
}
