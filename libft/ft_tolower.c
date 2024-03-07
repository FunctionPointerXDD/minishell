/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 10:57:54 by chansjeo          #+#    #+#             */
/*   Updated: 2023/10/14 19:38:28 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	unsigned char	ch;

	if (c < 0)
		return (c);
	ch = (unsigned char)c;
	if (ch >= 'A' && ch <= 'Z')
		ch += 'a' - 'A';
	return (ch);
}
