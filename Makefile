# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yokten <yokten@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/24 03:11:17 by yokten            #+#    #+#              #
#    Updated: 2023/12/24 05:46:48 by yokten           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
INC		=	minishell.
RM		=	rm -rf
LIBS += -lreadline
RL_FLAGS= -lft -L $(LIBFT) $(LIBS) -L ./lib/readline/lib
RL_INCS = --I. -I ./lib/readline/include


SRCS	=	main.c				\
			util.c				\
			util2.c				\
			util3.c 			\
			parser.c			\
			parser2.c			\
			list_util.c			\
			list_util2.c		\
			builtins.c 			\
			builtins2.c			\
			builtins3.c 		\
			exec.c 				\
			list_util3.c		\
			exec2.c				\
			redirections.c		\
			builtins4.c			\
			signals.c			\
			error_handler.c		\
			heredoc.c 			\
			parser3.c			\

CC = @gcc
NAME = minishell
CFLAGS = #-Wall -Wextra -Werror -g
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