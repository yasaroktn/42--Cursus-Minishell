NAME	=	minishell
CC		=	gcc
INC		=	minishell.h
CFLAGS	=	-Wall -Wextra -Werror -l readline
RM		=	rm -rf

SRCS	=	main.c	\
			utils.c \
			list_add.c

OBJS = $(SRCS:.c=.o)

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(INC)
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY: all, clean, fclean, re