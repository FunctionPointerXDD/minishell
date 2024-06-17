SRC = main.c utils.c utils_2.c utils_3.c free_struct.c seperate_quote.c \
		seperate_others.c seperate_others_2.c paren_stack.c check_syntax_error.c \
		expanse_wild_card.c expanse_wild_card_2.c expanse_wild_card_3.c \
		reorganize_args.c reorganize_args_2.c make_basic_parse_tree.c \
		make_basic_parse_tree_2.c make_complete_parse_tree.c parse_line.c
OBJ = $(SRC:.c=.o)
BONUS_SRC = 
BONUS_OBJ = $(BONUS_SRC:.c=.o)

CC = cc
CFLAGS = -Wextra -Wall -Werror -g
LIBFTFLAGS = -Llibft/ -lft
READLINEFLAGS = -lreadline

NAME = minishell

$(NAME) : $(OBJ)
		make -sC ./libft/ all bonus
		$(CC) $(CFLAGS) $(MLXFLAGS) $(LIBFTFLAGS) $(READLINEFLAGS) -o $(NAME) $(OBJ) 

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

bonus : $(BONUS_OBJ)
		make -sC ./libft/ all bonus
		$(CC) $(CFLAGS) $(MLXFLAGS) $(LIBFTFLAGS) -o $(NAME) $(BONUS_OBJ)
		touch $@

clean :
		rm -rf $(OBJ) $(BONUS_OBJ)
		make -sC ./libft/ clean

fclean :
		rm -rf $(OBJ) $(BONUS_OBJ) $(NAME) bonus
		make -sC ./libft/ fclean

re : 
		make fclean all