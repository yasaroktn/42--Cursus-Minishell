# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yokten <yokten@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 20:04:22 by yokten            #+#    #+#              #
#    Updated: 2023/11/18 05:13:43 by yokten           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
INC		=	minishell.
CFLAGS	=	-Wall -Wextra -Werror -g #-g -fsanitize=address
RM		=	rm -rf
LIBS += -lreadline

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


OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJS) $(LIBS) -o $(NAME) -lreadline
	@echo $(G)"[✓] "$(B)"minishell"

$(LIBFT) : 
	@make -C libft

%.o: %.c $(INC)
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft

re:	fclean all

git: 
	git add .
	git commit -m "auto commit"
	git push

.PHONY: all, clean, fclean, re