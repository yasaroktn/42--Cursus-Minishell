# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yokten <yokten@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 20:04:22 by yokten            #+#    #+#              #
#    Updated: 2023/11/29 13:35:00 by yokten           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
INC		=	minishell.
CFLAGS	=	-Wall -Wextra -Werror -g #-g -fsanitize=address
RM		=	rm -rf
LIBS += -lreadline
LIB 	= /lib/.minishell
RL_FLAGS= -lft -L $(LIBFT) $(LIBS) -L ./lib/readline/lib
RL_INCS = --I. -I ./lib/readline/include


SRCS	=	main.c				\
			lexer_list.c		\
			error_handling.c	\
			malloc.c			\
			builtins.c			\
			builtins2.c			\
			env_list.c 			\
			export.c			\
			expander.c			\
			builtins3.c 		\
			exec.c 				\
			pipe.c				\
			redirections.c		\
			signals.c			\

CC = @gcc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
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
	@make fclean -C lib/
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