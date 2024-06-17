/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:29:30 by sihong            #+#    #+#             */
/*   Updated: 2024/02/05 14:29:42 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_exit(char *msg, int exit_code)
{
	perror(msg);
	exit(exit_code);
}

void	rl_on_new_line_adv(void)
{
	if (rl_on_new_line() == -1)
		print_error_exit("minishell", 1);
}

void	*ft_calloc_adv(size_t count, size_t size)
{
	void	*output;

	output = ft_calloc(count, size);
	if (output == 0)
		print_error_exit("minishell", 1);
	return (output);
}

char	**ft_split_adv(const char *s, char c)
{
	char	**output;

	output = ft_split(s, c);
	if (output == 0)
		print_error_exit("minishell", 1);
	return (output);
}

char	*ft_substr_adv(const char *s, unsigned int start, size_t len)
{
	char	*output;

	output = ft_substr(s, start, len);
	if (output == 0)
		print_error_exit("minishell", 1);
	return (output);
}
