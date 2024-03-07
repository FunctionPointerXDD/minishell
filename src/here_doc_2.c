/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:45:30 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/06 20:52:26 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_here_doc(t_parse_list *tmp_lst, t_cmd_tool *cmd)
{
	char	*delimiter;
	char	tmp[28];

	while (tmp_lst)
	{
		if (ft_strncmp(tmp_lst->s, "<<", 3) == 0)
		{
			free(cmd->tmpfile);
			cmd->tmpfile = 0;
			delimiter = tmp_lst->file_name;
			ft_bzero(&tmp, 27);
			get_tmpfile(tmp);
			cmd->tmpfile = ft_strdup_adv(tmp);
			cmd->fd = open(cmd->tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd->fd < 0)
				perror("here_doc open");
			if (here_doc_write(cmd, delimiter) < 0)
				break ;
			cmd->here_doc_file[cmd->here_doc++] = ft_strdup_adv(cmd->tmpfile);
		}
		tmp_lst = tmp_lst->next;
	}
	cmd->here_doc_file[cmd->here_doc_cnt] = 0;
}

void	here_doc_init(t_parse_tree *root, t_cmd_tool *cmd)
{
	t_parse_list	*tmp_lst;

	if (root == 0 || cmd->escape == 1)
		return ;
	here_doc_init(root->left, cmd);
	tmp_lst = root->lst;
	run_here_doc(tmp_lst, cmd);
	here_doc_init(root->right, cmd);
}
