/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:04:30 by yokten            #+#    #+#             */
/*   Updated: 2023/11/27 21:07:37 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <sys/ioctl.h>

typedef struct s_lexer
{
	char			*content;
	int				type;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_export
{
	char			*content;
	struct s_export	*next;
}	t_export;

typedef struct s_core
{
	char			*input;
	t_lexer			*lexer;
	t_lexer			*lexer_head;
	t_env			*env;
	t_env			*env_head;
	t_export		*export;
	t_export		*export_head;
	pid_t			*pid;
	char			**expanded;
	char			**res;
	char			**arg;
	char 			**env2;
	int				i;
	int				j;
	int				k;
	int				l;
	int				t;
	int				p;
	int				s;
	int 			z;
	int				pipes[2];
	int				pipes2[2];
	int				lex_flag;
	int				control34;
	int				control39;
	int				exp_env_size;
	int				flag;
	int				flag1;
	int				flag2;
	int				flag3;
	int				child;
	int				err_code;
	char			*tmp_joined;
	char			*pwd;
	char			*readline;
	char			**tmp;
	char			*e_tmp;
	char			**exp_env;
	char			*swap;
	char			*expander;
	int				default_out;
	int 			process_iterator;
	int 			exec_fd;
	int fd[2];
}	t_core;

#endif
