/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:06:10 by chansjeo          #+#    #+#             */
/*   Updated: 2024/04/18 21:44:10 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include "../libft/libft.h"

# define MAX_PATH 1024 
# define INT_MAX 2147483647

extern int				g_signum;
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
}	t_env_list;

typedef struct s_env_info
{
	struct s_env_list	*head;
	struct s_env_list	*tail;
	int					exit_status;
	int					last_pid;
	int					escape;
	int					size;
}	t_env_info;

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
	struct s_run_parse_lst	*head;
	struct s_run_parse_lst	*tail;
	int						size;
	int						s_quote;
	int						d_quote;
	int						front_space;
	int						rear_space;
}	t_run_parse_info;

typedef struct s_run_parse_lst
{
	char					*token;
	t_parse_type			t_type;
	struct s_run_parse_lst	*next;
	struct s_run_parse_lst	*prev;
}	t_run_parse_lst;

typedef struct s_cmd_tool
{
	char	*path;
	char	**execve_argv;
	char	*tmpfile;	
	char	**here_doc_file;
	int		here_doc_cnt;
	int		here_doc;
	int		escape;
	char	**envp;
	pid_t	pid;
	int		pipe_fd[2];
	int		prev_fd;
	int		fd;
	int		is_builtin;
	int		is_pipe;
	int		error_code;
}	t_cmd_tool;

/*------ chansjeo ------*/
/*signal_handler.c*/
void				sigquit_handler(int signum);
void				sigint_handler(int signum);
void				signal_handler(int signum);
void				heredoc_sigint(int signum);

/*builtin.c*/
int					cmd_exit(char **arg, int exit_status);
int					cmd_echo(char **arg);
int					cmd_export(t_env_info *info, char **arg);
int					cmd_unset(t_env_info *info, char **arg);
int					is_valid(char *param);

/*builtin_2.c*/
int					cmd_cd(char *path);
int					cmd_pwd(void);
int					cmd_env(t_env_info *info);
int					cmd_exit(char **arg, int exit_status);
int					scan_digit(char *str);

/*is_valid.c*/
int					is_valid(char *param);

/*env_list.c*/
t_env_info			*init_env(char	**envp);
char				*get_env_key(t_env_info *info, char *data);
char				*get_env_value(t_env_info *info, char *data);
t_env_info			*make_env_list(t_env_info *info, char **envp);
char				**list_to_argv(t_env_info *info);

/*env_list_2.c*/
int					delete_env(t_env_info *info, char *param);
void				find_env_check_equal(char *equal1, char *equal2);
t_env_list			*find_env(t_env_info *info, char *param);
int					insert_env(t_env_info *info, char *param);
void				init_info(t_env_info *dummy);

/*run_command.c*/
void				run_command(t_env_info *info, \
					t_parse_tree *root, t_cmd_tool *cmd);
void				exec_cmd_with_pipe(t_env_info *info, \
					t_parse_list *root, t_cmd_tool *cmd);
void				select_run(t_parse_list *lst, t_env_info *info);
void				last_running(t_env_info *info, t_parse_list *tmp, \
					t_cmd_tool *cmd);
void				general_running(t_env_info *info, t_parse_list *tmp, \
					t_cmd_tool *cmd);

/*run_command_2.c*/
int					exec_builtin(t_env_info *info, char **arg);
void				push_command(t_env_info *info, t_cmd_tool *cmd);
void				exec_child(t_env_info *info, t_parse_list *lst, \
					t_cmd_tool *cmd);
void				exec_cmd_at_builtin(t_env_info *info, \
					t_parse_list *lst, t_cmd_tool *cmd);
void				exec_cmd(t_env_info *info, t_parse_list *lst, \
					t_cmd_tool *cmd);

/*run_command_utils.c*/
void				all_close(t_cmd_tool *cmd);
char				**count_execve_args(t_parse_list *tmp);
char				**join_args(t_parse_list *lst);
int					is_builtin(char **arg);
t_parse_list		*check_pipe(t_parse_list *lst);

/*run_command_utils_2.c*/
void				update_here_doc(t_parse_list *lst, t_cmd_tool *cmd);
int					wait_proc(t_env_info *info);
void				init_fd(t_cmd_tool *cmd);

/* operaotor.c */
void				oper_redir(t_parse_list *lst, t_cmd_tool *cmd);
void				oper_pipex(t_cmd_tool *cmd);
void				redir_to_file(t_parse_list *tmp, t_cmd_tool *cmd, \
					int stdnum);
void				redir_to_here_doc(t_cmd_tool *cmd);

/*here_doc.c*/
int					here_doc_write(t_cmd_tool *cmd, char *delimiter);
void				read_here_doc(t_cmd_tool *cmd, char **tmp, char *delimiter);
void				count_here_doc(t_parse_tree *root, t_cmd_tool *cmd);
void				create_here_doc_stack(t_cmd_tool *cmd);
void				get_tmpfile(char buf[]);

/*here_doc_2.c*/
void				here_doc_init(t_parse_tree *root, t_cmd_tool *cmd);
void				run_here_doc(t_parse_list *tmp_lst, t_cmd_tool *cmd);

/*cmd_check.c*/
void				cmd_check(t_cmd_tool *cmd, char *param, char **envp);
int					filtering_cmd(t_cmd_tool *cmd, char *param);
void				filtering2(t_cmd_tool *cmd, char *param);
int					check_slash(char *param);
int					is_blank(char *param);
char				**path_parser(char *path_line, char *param);
char				*get_path_line(char **envp);
void				put_error(char *param, int code);
void				free_all(char **path_list, int cnt, t_cmd_tool *cmd, \
				char *param);
int					ft_isspace(int c);

/*parse_for_expanse.c*/
char				**parse_for_expansion(char **argv, t_env_info *info);
char				*get_replace(t_run_parse_lst *tmp, t_env_info *env_info);
t_run_parse_info	*parse_var_expansion(t_run_parse_info *info, \
					t_env_info *env_info);
char				**make_char_frame(t_run_parse_info *info);
char				**parse_to_char(t_run_parse_info *info, int i);
/*parse_for_expanse_2.c*/
size_t				ft_strcspn(t_run_parse_info *info, const char *str, \
					char *reject);
void				insert_quote_node(t_run_parse_info *info, char *str);
int					var_len(char *tmp);
size_t				insert_var_node(t_run_parse_info *info, char *str);
void				strsep_to_list(t_run_parse_info *info, char *str);
/*parse_for_expanse_3.c*/
t_run_parse_info	*init_parse_info(void);
int					insert_node(t_run_parse_info *info, char *str, int type);
int					delete_node(t_run_parse_info *info, t_run_parse_lst *node);
void				insert_space_node(t_run_parse_info *info);
t_run_parse_info	*parse_create(t_run_parse_info *info, char **argv);
/*parse_for_expanse_4.c*/
void				reconnect_node(t_run_parse_lst *tmp, \
					t_run_parse_lst *tmp_prev, char *buf);
void				reconnect_space_node(t_run_parse_lst *tmp, \
					t_run_parse_lst *tmp_prev);
void				split_to_list(t_run_parse_info *info, \
					t_run_parse_lst *tmp, char **bufs);
void				info_space(t_run_parse_info *info, t_run_parse_lst *tmp);
t_run_parse_info	*parse_word_split(t_run_parse_info *info, int type);
/*parse_for_expanse_5.c*/
void				reformat_node(t_run_parse_info *info, \
					t_run_parse_lst *start, char *res);
int					apply_wild_card(t_run_parse_info *info, \
					t_run_parse_lst *tmp);
int					check_wildcard(t_run_parse_lst *tmp);
void				dispose_wildcard(t_run_parse_info *info);
t_run_parse_info	*parse_quote(t_run_parse_info *info);
/*parse_for_expanse_6.c*/
void				info_quote(t_run_parse_info *info, t_run_parse_lst *tmp);
void				clear_node_and_argv(t_run_parse_info *info, char **argv);

/* main.c */
void				init_cmd_tool(t_cmd_tool *cmd);

/*-------- sihong --------*/
//utils.c
void				print_error_exit(char *msg, int exit_code);
void				rl_on_new_line_adv(void);
void				*ft_calloc_adv(size_t count, size_t size);
char				**ft_split_adv(const char *s, char c);
char				*ft_substr_adv(const char *s, unsigned int start, \
					size_t len);
//utils_2.c
int					check_blank(t_parse_list *node);
char				*ft_strdup_adv(char *s);
char				*ft_strjoin_adv(char *s1, char *s2);
int					split_len(char **s);
void				free_split(char **s);
//utils_3.c
DIR					*opendir_adv(char *s);
//free_struct.c
void				free_wild_key_lst(t_wild_key_lst *head);
void				free_parse_list(t_parse_list *head);
void				free_parse_tree(t_parse_tree *root);
void				free_all_env(t_env_info *info);
//seperate_quote.c
void				write_quote_syntax_error(char quote);
int					make_quote_node(char *line, t_parse_list **tmp, \
					int *anchor, int *i);
void				substr_args(char *line, t_parse_list **tmp, \
					int *anchor, int *i);
t_parse_list		*seperate_quote(char *line);
//seperate_others.c
int					check_operator(char *s);
void				make_args_node(char *s, int *i, t_parse_list **lst2_tmp);
void				make_operator_node(char *s, t_parse_list **lst2_tmp, \
					int *i);
void				make_other_node(char *s, t_parse_list **lst2_tmp);
t_parse_list		*seperate_others(t_parse_list *lst1_head);
//seperate_others_2.c
void				make_paren_node(char *s, t_parse_list **lst2_tmp, int *i);
void				rm_none_node(t_parse_list *head);
//paren_stack.c
t_paren_stack		*new_paren_stack(char paren);
void				push_paren_stack(char paren, t_paren_stack **top);
void				pop_paren_stack(t_paren_stack **top);
void				free_paren_stack(t_paren_stack **top);
//check_syntax_error.c
int					check_empty_paren(t_parse_list *head);
int					check_overlapped_paren(t_parse_list *head);
int					check_tree_syntax_error(t_parse_tree *root);
int					check_list_syntax_error_2(t_token_type tmp, \
					t_parse_list *head);
int					check_list_syntax_error(t_parse_list *head);
//expanse_wild_card_4.c
int					get_key_len(char *s, int start, int end);
//expanse_wild_card_3.c
void				get_key_2(char *s, char *key, int start, int end);
char				*get_key(char *s, int start, int end);
void				get_key_lst_skip_quote(char *s, int *i);
int					get_key_lst_make_key_node(char *s, int *i, int *anchor, \
					t_wild_key_lst **key_tmp);
t_wild_key_lst		*get_key_lst(char *s);
//expanse_wild_card_2.c
int					get_expansed_s_case_key_start(t_wild_key_lst **kl, \
					char *d_name, int *i);
int					get_expansed_s_check_key(char *d_name, int *i, \
					t_wild_key_lst *kl);
void				get_expansed_s_append_s(int i, char *d_name, \
					char **expansed_s);
int					get_expansed_s_2(t_wild_key_lst **kl, char *d_name, int *i);
void				get_expansed_s(t_wild_key_lst *kl, \
					char *d_name, char **expansed_s);
//expanse_wild_card.c
void				expanse_s(char **s);
void				expanse_wild_card(t_parse_list *head);
//reorganize_args_2.c
void				rm_blank_after_pipex(t_parse_list *lst);
void				qoute_rollback_space(char **s);
void				quote_replace_space(char *s);
//reorganize_args.c
void				alloc_filename_2(int *i, t_parse_list *head);
void				alloc_filename(t_parse_list *head);
void				organize_args_2(t_parse_list *head_tmp, t_parse_list **lst);
t_parse_list		*organize_args(t_parse_list *lst);
t_parse_list		*reorganize_args(t_parse_list *lst);
//make_basic_parse_tree.c
void				make_logic_tree_node(t_parse_tree *tree_tmp, \
					t_parse_list **head);
int					make_paren_tree_node_3(t_paren_stack **paren_top, \
					t_parse_list **head);
void				make_paren_tree_node_2(t_parse_tree *tree_tmp, \
					t_parse_list **head, t_paren_stack **paren_top);
int					make_paren_tree_node(t_parse_tree *tree_tmp, \
					t_parse_list **head);
t_parse_tree		*make_basic_parse_tree(t_parse_list *head);
//make_basic_parse_tree_2.c
void				balance_parse_tree(t_parse_tree **root);
int					make_basic_parse_tree_3(t_parse_tree *tree_tmp, \
					t_parse_tree *root, t_parse_list **head);
void				make_basic_parse_tree_2(t_parse_tree **root);
void				break_lst_link(t_parse_list **head);
void				make_args_tree_node(t_parse_tree *tree_tmp, \
					t_parse_list **head);
//make_complete_parse_tree.c
int					make_complete_parse_tree_2(t_parse_tree **root);
int					make_complete_parse_tree(t_parse_tree **root);
//parse_line.c
int					parse_line_2(t_parse_tree **root);
t_parse_tree		*parse_line(char *line);

#endif
