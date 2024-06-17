/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:58:26 by sihong            #+#    #+#             */
/*   Updated: 2024/02/05 11:58:28 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>

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