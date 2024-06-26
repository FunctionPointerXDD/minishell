/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 20:42:31 by chansjeo          #+#    #+#             */
/*   Updated: 2023/10/17 11:09:34 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	unsigned char	ch;

	if (c < 0)
		return (c);
	ch = c;
	if (ch >= 'a' && ch <= 'z')
		ch -= 'a' - 'A';
	return ((int)ch);
}
