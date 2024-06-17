/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:05:49 by chansjeo          #+#    #+#             */
/*   Updated: 2023/10/26 20:11:22 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	const unsigned char	*us;

	us = (const unsigned char *)s;
	while (*us != (unsigned char)c)
	{
		if (*us == '\0')
			return (0);
		us++;
	}
	return ((char *)us);
}
