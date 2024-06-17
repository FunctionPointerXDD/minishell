/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:32:46 by sihong            #+#    #+#             */
/*   Updated: 2023/10/16 20:33:39 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	int				fd;
	char			*buf;
	size_t			store;
	struct s_list	*next;
	int				is_end;
}	t_list;

void	free_data(t_list **head);
void	*ft_calloc_cp(size_t count, size_t size);
char	*ft_substr_cp(char const *s, size_t start, size_t len, size_t buf_size);
int		is_head_null(t_list **head, int fd);
char	*get_next_line(int fd);
int		read_line(t_list *head, char **result, size_t i, int fd);
int		change_buf_size(size_t *buf_size, size_t *i, t_list *head);
int		end_with_nl(t_list *head, size_t buf_size, size_t *i, char **result);
int		set_data(size_t *buf_size, size_t *i, t_list **head, int fd);
char	*read_file(t_list *head, int fd);

#endif
