/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:06:51 by chansjeo          #+#    #+#             */
/*   Updated: 2024/02/14 13:42:41 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*addr;

	if (count != 0 && size > (size_t)(-1) / count)
		return (0);
	addr = (void *)malloc(count * size);
	if (addr == 0)
		return (0);
	ft_memset(addr, 0, (count * size));
	return (addr);
}
