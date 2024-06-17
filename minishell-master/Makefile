NAME = minishell

SRCS = main.c env_list.c builtin.c run_command.c operator.c cmd_check.c \
	   utils.c utils_2.c utils_3.c free_struct.c seperate_quote.c \
	   seperate_others.c seperate_others_2.c paren_stack.c check_syntax_error.c \
	   expanse_wild_card.c expanse_wild_card_2.c expanse_wild_card_3.c \
	   reorganize_args.c reorganize_args_2.c make_basic_parse_tree.c \
	   make_basic_parse_tree_2.c make_complete_parse_tree.c parse_line.c \
	   parse_for_expanse.c 
OBJS = $(SRCS:.c=.o)

BNS_SRCS = main_bonus.c
BNS_OBJS = $(BNS_SRCS:.c=.o)

INC = minishell.h
BNS_INC = minishell_bonus.h

CC = cc
CFLAGS = -Wall -Werror -Wextra
LINK = -lreadline
# DFLAG = -g -fsanitize=address
LIBFT = libft/libft.a
RM = rm -rf
MAKE = make

all: $(NAME)

bonus : BONUS

$(NAME): $(LIBFT) $(OBJS) $(INC)
	$(CC) $(DFLAG) $(CFLAGS) $(LINK) $(OBJS) $(LIBFT) -o $@
	$(RM) BONUS

$(OBJS): $(SRCS)
	$(CC) $(DFLAG) $(CFLAGS) -c $(SRCS)

BONUS: $(LIBFT) $(BNS_OBJS) $(BNS_INC)
	$(CC) $(DFLAG) $(CFLAGS) $(LINK) $(BNS_OBJS) $(LIBFT) -o $(NAME)
	touch $@

$(BNS_OBJS): $(BNS_SRCS)
	$(CC) -g $(CFLAGS) -c $(BNS_SRCS)

$(LIBFT):
	$(MAKE) -sC libft all

%.a: lib
	$(MAKE) $(@F) -C $(@D)

clean:
	$(RM) $(OBJS) $(DEPS) $(BNS_OBJS) $(BNS_DEPS) BONUS
	$(MAKE) -sC libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -sC libft fclean

re: fclean all

.PHONY: all clean fclean re bonus
