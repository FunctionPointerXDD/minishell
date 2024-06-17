/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:06:09 by sihong            #+#    #+#             */
/*   Updated: 2024/02/23 19:08:33 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_leak(void)
{
	system("leaks minishell");
}

int	main(/*int argc, char **argv, char **evnp*/)
{
	char	*line;
	t_parse_tree	*root;

	while (1)
	{
		line = readline("minishell$ ");
		if (line == 0 || ft_strncmp("exit", line, 5) == 0)
		{
			free(line);
			break ;
		}
		rl_on_new_line_adv();
		add_history(line);
		root = parse_line(line);
		if (root)
		{
			print_tree(root);
			free_parse_tree(root);
		}
		free(line);
		check_leak();
	}
}
