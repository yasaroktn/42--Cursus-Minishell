# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yokten <yokten@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/24 03:11:17 by yokten            #+#    #+#              #
#    Updated: 2023/12/28 07:49:49 by yokten           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
INC		=	minishell.
RM		=	rm -rf
LIBS += -lreadline
RL_FLAGS= -lft -L $(LIBFT) $(LIBS) -L ./lib/readline/lib
RL_INCS = --I. -I ./lib/readline/include


SRCS	=	main/main.c				\
			main/error_handler.c	\
			until/util.c			\
			until/util2.c			\
			until/util3.c 			\
			parser/parser.c			\
			parser/parser2.c		\
			parser/parser3.c		\
			list/list_util.c		\
			list/list_util2.c		\
			list/list_util3.c		\
			builtin/builtins.c 		\
			builtin/builtins2.c		\
			builtin/builtins3.c 	\
			builtin/builtins4.c		\
			executer/exec.c 		\
			executer/exec2.c		\
			redir/redirections.c	\
			redir/heredoc.c 		\
			signal/signals.c		\

CC = @gcc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
RM = @rm -rf
LIBFT = libft/libft.a
OBJS = $(SRCS:.c=.o)

READLINE = readline

all: $(READLINE) $(NAME)

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=${PWD}/readline
	cd readline-8.2 && make install


$(NAME): $(OBJS)  $(LIBFT)
	$(CC) -o $(NAME) $(OBJS)  $(LIBFT) $(CFLAGS) -L${PWD}/readline/lib  -I${PWD}/readline/include/ -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/readline/include/
  $(LIBFT) : 
	@make -C libft
fclean: clean
	$(RM) $(NAME)
	@make fclean -C libft
	@rm -rf readline-8.2 readline-8.2.tar.gz

git:
	@make fclean
	git add .
	git commit -m "auto commit"
	git push

clean:
	$(RM) $(OBJS)

re: fclean all

.PHONY: all fclean clean re