/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:13:50 by yokten            #+#    #+#             */
/*   Updated: 2023/12/24 03:13:53 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
}	t_exp;

typedef struct s_main
{
	char	*input;
	char	*shell_name;
	t_lexer	*lexer_list;
	t_lexer	*lexer_head;
	t_lexer	*lexer_tmp;
	t_env	*env_head;
	t_env	*env_list;
	t_exp	*export_list;
	t_exp	*export_head;
	int		i;
	int		j;
	int		a;
	int		b;
	int		c;
	int		l;
	int		k;
	int		z;
	int		x;
	int		y;
	int		q;
	int		r;
	int		redir_count;
	int		dollar;
	int		pipe_count;
	int		parse_flag;
	int		single_q;
	int		double_q;
	char	*temp_string;
	char	*tmp;
	char	*dq_temp;
	int		flag;
	char	*pwd;
	char	*export_tmp;
	char	**temp_env;
	int		process_iterator;
	int		exec_fd;
	char	**arg;
	char	**env2;
	char	**res;
	char	*tmp_joined;
	int		io[2];
	int		heredoc_fd[2];
	int		*pid;
	int		heredoc_flag;
	int		err_no;
	pid_t	pid2;
}	t_main;

#endif