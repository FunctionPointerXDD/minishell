/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:52:51 by sihong            #+#    #+#             */
/*   Updated: 2024/03/06 16:03:57 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_blank(t_parse_list *node)
{
	int	i;

	if (node == 0)
		return (0);
	if (node->token_type == args || node->token_type == organized_args)
	{
		i = 0;
		while (node->s[i] == ' ')
			i += 1;
		if (node->s[i] == 0)
			return (1);
	}
	return (0);
}

char	*ft_strdup_adv(char *s)
{
	char	*s_dup;

	s_dup = ft_strdup(s);
	if (s_dup == 0)
		print_error_exit("minishell", 1);
	return (s_dup);
}

char	*ft_strjoin_adv(char *s1, char *s2)
{
	char	*s;

	if (s1 != 0 && s2 == 0)
		s = ft_strdup_adv(s1);
	else if (s1 == 0 && s2 != 0)
		s = ft_strdup_adv(s2);
	else if (s1 == 0 && s2 == 0)
		return (0);
	else
	{
		s = ft_strjoin(s1, s2);
		if (s == 0)
			print_error_exit("minishell", 1);
	}
	return (s);
}

int	split_len(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	free_split(char **s)
{
	int	i;

	if (s == 0)
		return ;
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
