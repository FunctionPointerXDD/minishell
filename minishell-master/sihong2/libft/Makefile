SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
		ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
		ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
		ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
		ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
		get_next_line.c get_next_line_utils.c \
		form_flag_width.c form_percent.c form_precision.c form_sign.c form_string.c ft_printf.c print_hex_form.c set_conditions.c ft_uitoa.c \

OBJ = $(SRC:.c=.o)

BONUSSRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
BONUSOBJ = $(BONUSSRC:.c=.o)

CC = cc
CFLAGS = -Wextra -Wall -Werror

NAME = libft.a

$(NAME) : $(OBJ)
		ar -rcus $(NAME) $(OBJ)

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

bonus : $(BONUSOBJ)
		ar -rcus $(NAME) $(BONUSOBJ)
		touch $@

clean :
		rm -rf $(OBJ) $(BONUSOBJ)

fclean :
		rm -rf $(OBJ) $(BONUSOBJ) $(NAME) bonus

re : 
	make fclean all