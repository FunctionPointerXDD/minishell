/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:05:17 by sihong            #+#    #+#             */
/*   Updated: 2023/10/06 15:05:35 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void	*temp;
	size_t	count;

	temp = b;
	count = 0;
	while (count < len)
	{
		*(unsigned char *)b = (unsigned char)c;
		if (*(unsigned char *)b != (unsigned char)c)
			return (0);
		b++;
		count++;
	}
	return (temp);
}
