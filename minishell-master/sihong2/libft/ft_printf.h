/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:17:09 by sihong            #+#    #+#             */
/*   Updated: 2023/10/25 13:17:21 by sihong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

# define ERROR -1

typedef struct s_sign_list
{
	int	c;
	int	s;
	int	p;
	int	d;
	int	i;
	int	u;
	int	x;
	int	upper_x;
	int	percent_sign;
}	t_sign_list;

typedef struct s_flag_list
{
	int	minus;
	int	zero;
	int	hash;
	int	space;
	int	plus;
	int	precision;
	int	width;
	int	precision_len;
}	t_flag_list;

typedef struct s_list_pt
{
	t_sign_list	sign;
	t_flag_list	flag;
}	t_list_pt;

typedef struct s_i_list
{
	size_t	i;
	size_t	s_i;
	size_t	buffer_size;
}	t_i_list;

int		is_x_zero(char *input);
int		flag_hash(char **input, t_list_pt *cond);
int		flag_plus_space(char **input, t_list_pt *cond);
char	*form_flag(char **input, t_list_pt *cond);
void	form_flag_case_paste_at_right(char **input, t_list_pt *cond,
			char *temp);
int		form_precision_case_new_form(t_list_pt *cond, char **result,
			char *temp);
char	*form_percent(const char *format, size_t *i, va_list *arg_pointer,
			int *is_c_null);
int		form_sign_char_s(t_list_pt *cond, va_list *arg_point, char **result);
int		form_sign_char(t_list_pt *cond, va_list *arg_point, char **result);
int		form_sign_hex(t_list_pt *cond, va_list *arg_point, char **result);
int		form_sign_dec(t_list_pt *cond, va_list *arg_point, char **result);
char	*form_sign(t_list_pt *cond, va_list *arg_point);
int		form_precision_string(t_list_pt *cond, char **result);
char	*form_precision(t_list_pt *cond, char **result);
int		resize_buf(char **storage, size_t *buf_size);
void	check_c_null(char **storage, t_i_list *i_list, int is_c_null);
int		when_return_percent_sign(const char *format, char **storage,
			va_list *arg_pointer, t_i_list *i_list);
int		form_string(const char *format, char **storage, size_t buf_size,
			va_list *arg_pointer);
void	put_hex_char(char *result, size_t num, int i, int is_upper);
size_t	find_hex_len(size_t num);
char	*print_hex_form(size_t num, int show_0x, int is_upper);
void	check_error(t_list_pt *cond);
int		check_sign(const char *format, t_list_pt *cond, size_t *i);
void	check_precision(const char *format, t_list_pt *cond, size_t *i);
void	check_flag_width(const char *format, t_list_pt *cond, size_t *i);
void	set_list_zero(t_list_pt *cond);
int		ft_printf(const char *format, ...);
char	*ft_uitoa(unsigned int n);

#endif