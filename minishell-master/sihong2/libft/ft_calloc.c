/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:03:56 by sihong            #+#    #+#             */
/*   Updated: 2023/10/07 15:03:58 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;
	char	*result_copy;
	size_t	i;

	result = malloc(size * count);
	if (result == 0)
		return (0);
	result_copy = (char *)result;
	i = 0;
	while (i < size * count)
		result_copy[i++] = 0;
	return (result);
}
