/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:12:12 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/07 13:55:12 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signum;

void	sigquit_handler(int signum)
{
	(void)signum;
	write(1, "Quit: 3\n", 8);
}

void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}

void	signal_handler(int signum)
{
	(void)signum;
	g_signum = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_sigint(int signum)
{
	(void)signum;
	g_signum = SIGINT;
	close(0);
}
