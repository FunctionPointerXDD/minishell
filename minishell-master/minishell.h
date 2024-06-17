/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:06:10 by chansjeo          #+#    #+#             */
/*   Updated: 2024/03/01 17:40:22 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include "libft/libft.h"

# define MAX_PATH 1024 
# define INT_MAX 2147483647
# define MAX_TMP_FILE 100

extern int g_signum;
/*parse struct*/
typedef struct dirent	t_dirent;

typedef enum e_token_type
{
	none,
	double_quote = 34,
	single_quote = 39,
	args,
	redirection,
	pipex,
	logical,
	parenthesis,
	organized_args
}	t_token_type;

typedef struct s_parse_list
{
	char				*s;
	struct s_parse_list	*next;
	t_token_type		token_type;
	char				**execve_args;
	char				*file_name;
}	t_parse_list;

typedef struct s_wild_key_lst
{
	char					*key;
	struct s_wild_key_lst	*next;
	int						wild;
}	t_wild_key_lst;

typedef struct s_paren_stack
{
	char					paren;
	struct s_paren_stack	*next;
}	t_paren_stack;

typedef struct s_parse_tree
{
	t_token_type		type;
	t_parse_list		*lst;
	struct s_parse_tree	*left;
	struct s_parse_tree	*right;
}	t_parse_tree;

/*opertion struct*/
typedef struct s_env_list
{
	char				*data;
	struct s_env_list	*next;
	struct s_env_list	*prev;
} t_env_list;

typedef struct s_env_info
{
	struct s_env_list	*head;
	struct s_env_list	*tail;
	int					exit_status;
	int					escape;
	int					size;
} t_env_info;

typedef enum e_parse_type
{
	words,
	var,
	space,
	wild_card,
	p_d_quote = 34,
	p_s_quote = 39,
}	t_parse_type;

typedef struct s_run_parse_info
{
	struct s_run_parse_lst *head;
	struct s_run_parse_lst *tail;
	int						size;
	int						s_quote;
	int						d_quote;
	int						front_space;
	int						rear_space;
} t_run_parse_info;

typedef struct	s_run_parse_lst
{
	char					*token;
	t_parse_type 			t_type;
	struct s_run_parse_lst	*next;
	struct s_run_parse_lst	*prev;
} t_run_parse_lst;

typedef struct s_cmd_tool
{
	char	*path;
	char	**execve_argv;
	char	*tmpfile;	
	char	**here_doc_file;
	int		here_doc_cnt;
	int		here_doc;
	char	**envp;
	pid_t	pid;
	int		pipe_fd[2];
	int		prev_fd;
	int		fd;
	int		is_builtin;
	int		error_code;
} t_cmd_tool;

/*------ chansjeo ------*/
/*builtin.c*/
int	cmd_exit(char **arg, int exit_status);
int	cmd_echo(char **arg);
int	cmd_cd(t_env_info *info, char *path);
int	cmd_pwd();
int	cmd_export(t_env_info *info, char **arg);
int	cmd_env(t_env_info *info);
int	cmd_unset(t_env_info *info, char **arg);
int	is_valid(char *param);

/*env_list.c*/
t_env_info	*init_env(char	**envp);
int	delete_env(t_env_info *info, char *param);
t_env_list	*find_env(t_env_info *info, char *param);
char	*get_env_key(t_env_info *info, char *data);
char	*get_env_value(t_env_info *info, char *data);
t_env_info	*make_env_list(t_env_info *info, char **envp);
int insert_env(t_env_info *info, char *param);
char	**list_to_argv(t_env_info *info);
char	*format_dollar_sign(t_env_info *info, char *str);

/*run_command.c*/
void	run_command(t_env_info *info, t_parse_tree *root, t_cmd_tool *cmd);
int		exec_builtin(t_env_info *info, char **arg);
void	exec_cmd_with_pipe(t_env_info *info, t_parse_list *root, t_cmd_tool *cmd);
void	exec_cmd(t_env_info *info, t_parse_list *lst, t_cmd_tool *cmd);
t_parse_list	*check_pipe(t_parse_list *lst);
int		wait_proc(t_env_info *info);
void	select_run(t_parse_list *lst, t_env_info *info);
void	all_close(t_cmd_tool *cmd);

/* operaotor.c */
void	oper_redir(t_env_info *info, t_parse_list *lst, t_cmd_tool *cmd);
void    oper_pipex(t_env_info *info, t_parse_list *lst, t_cmd_tool *cmd);
void	put_error(char *cmd, int code);
void	here_doc_init(t_parse_tree *root, t_cmd_tool *cmd);
int		here_doc_write(t_cmd_tool *cmd, char *delimiter);
void	count_here_doc(t_parse_tree *root, t_cmd_tool *cmd);
void	create_here_doc_stack(t_cmd_tool *cmd);
void	get_tmpfile(char buf[]);

/*cmd_check.c*/
char	**path_parser(char *path_line, char *param);
char	*get_path_line(char **envp);
int		free_and_return(char **path_list, int cnt);
void	cmd_check(t_cmd_tool *cmd, char *param, char **envp);
int		is_blank(char *param, t_cmd_tool *cmd);

char	**parse_for_expansion(char **argv, t_env_info *info);
/* main.c */
void	init_cmd_tool(t_cmd_tool *cmd);

/*-------- sihong --------*/
//utils.c
void			print_error_exit(char *msg, int exit_code);
void			rl_on_new_line_adv(void);
void			*ft_calloc_adv(size_t count, size_t size);
char			**ft_split_adv(const char *s, char c);
char			*ft_substr_adv(const char *s, unsigned int start, size_t len);
//utils_2.c
int				check_blank(t_parse_list *node);
char			*ft_strdup_adv(char *s);
char			*ft_strjoin_adv(char *s1, char *s2);
int				split_len(char **s);
void			free_split(char **s);
//utils_3.c
DIR				*opendir_adv(char *s);
//free_struct.c
void			free_wild_key_lst(t_wild_key_lst *head);
void			free_parse_list(t_parse_list *head);
void			free_parse_tree(t_parse_tree *root);
//seperate_quote.c
void			write_quote_syntax_error(char quote);
int				make_quote_node(char *line, t_parse_list **tmp, \
				int *anchor, int *i);
void			substr_args(char *line, t_parse_list **tmp, \
				int *anchor, int *i);
t_parse_list	*seperate_quote(char *line);
//seperate_others.c
int				check_operator(char *s);
void			make_args_node(char *s, int *i, t_parse_list **lst2_tmp);
void			make_operator_node(char *s, t_parse_list **lst2_tmp, int *i);
void			make_other_node(char *s, t_parse_list **lst2_tmp);
t_parse_list	*seperate_others(t_parse_list *lst1_head);
//seperate_others_2.c
void			make_paren_node(char *s, t_parse_list **lst2_tmp, int *i);
void			rm_none_node(t_parse_list *head);
//paren_stack.c
t_paren_stack	*new_paren_stack(char paren);
void			push_paren_stack(char paren, t_paren_stack **top);
void			pop_paren_stack(t_paren_stack **top);
void			free_paren_stack(t_paren_stack **top);
//check_syntax_error.c
int				check_empty_paren(t_parse_list *head);
int				check_overlapped_paren(t_parse_list *head);
int				check_tree_syntax_error(t_parse_tree *root);
int				check_list_syntax_error_2(t_token_type tmp, t_parse_list *head);
int				check_list_syntax_error(t_parse_list *head);
//expanse_wild_card_3.c
int				get_key_len(char *s, int start, int end);
char			*get_key(char *s, int start, int end);
void			get_key_lst_skip_quote(char *s, int *i);
int				get_key_lst_make_key_node(char *s, int *i, int *anchor, \
				t_wild_key_lst **key_tmp);
t_wild_key_lst	*get_key_lst(char *s);
//expanse_wild_card_2.c
int				get_expansed_s_case_key_start(t_wild_key_lst **kl, \
				char *d_name, int *i);
int				get_expansed_s_check_key(char *d_name, int *i, \
				t_wild_key_lst *kl);
void			get_expansed_s_append_s(int i, char *d_name, char **expansed_s);
void			get_expansed_s(t_wild_key_lst *kl, \
				char *d_name, char **expansed_s);
//expanse_wild_card.c
void			expanse_s(char **s);
void			expanse_wild_card(t_parse_list *head);
//reorganize_args_2.c
void			rm_blank_after_pipex(t_parse_list *lst);
void			qoute_rollback_space(char **s);
void			quote_replace_space(char *s);
//reorganize_args.c
void			alloc_filename_2(int *i, t_parse_list *head);
void			alloc_filename(t_parse_list *head);
void			organize_args_2(t_parse_list *head_tmp, t_parse_list **lst);
t_parse_list	*organize_args(t_parse_list *lst);
t_parse_list	*reorganize_args(t_parse_list *lst);
//make_basic_parse_tree.c
void			make_logic_tree_node(t_parse_tree *tree_tmp, \
				t_parse_list **head);
int				make_paren_tree_node_3(t_paren_stack **paren_top, \
				t_parse_list **head);
void			make_paren_tree_node_2(t_parse_tree *tree_tmp, \
				t_parse_list **head, t_paren_stack **paren_top);
int				make_paren_tree_node(t_parse_tree *tree_tmp, \
				t_parse_list **head);
t_parse_tree	*make_basic_parse_tree(t_parse_list *head);
//make_basic_parse_tree_2.c
void			balance_parse_tree(t_parse_tree **root);
int				make_basic_parse_tree_3(t_parse_tree *tree_tmp, \
				t_parse_tree *root, t_parse_list **head);
void			make_basic_parse_tree_2(t_parse_tree **root);
void			break_lst_link(t_parse_list **head);
void			make_args_tree_node(t_parse_tree *tree_tmp, \
				t_parse_list **head);
//make_complete_parse_tree.c
int				make_complete_parse_tree_2(t_parse_tree **root);
int				make_complete_parse_tree(t_parse_tree **root);
//parse_line.c
t_parse_tree	*parse_line(char *line);
//imsi
void			print_tree(t_parse_tree *root);

#endif