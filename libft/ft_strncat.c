/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:48:56 by chansjeo          #+#    #+#             */
/*   Updated: 2023/12/05 13:14:58 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	char	*ret;

	ret = dest;
	if (nb != 0)
	{
		while (*dest != '\0')
			dest++;
		*dest = *src;
		while (*dest != '\0')
		{
			++dest;
			++src;
			*dest = *src;
			if (--nb == 0)
			{
				*dest = '\0';
				break ;
			}
		}
	}
	return (ret);
}
