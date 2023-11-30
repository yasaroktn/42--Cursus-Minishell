/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:03:17 by yokten            #+#    #+#             */
/*   Updated: 2023/11/30 11:10:52 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define NULLFLAG 0xbebebebebebebebe

# include <stddef.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include "structs.h"
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdint.h>

t_lexer		*lexer_listnew(char *content);
t_lexer		*lexer_lstlast(t_lexer *lst);
t_env		*env_listnew(char *content);
t_export	*export_listnew(char *content);
void		ft_unset_management(t_core *core);
void		lexer_lstadd_back(t_lexer **lst, t_lexer *new);
void		env_lstadd_back(t_env **lst, t_env *new);
void		export_lstadd_back(t_export *lst, t_export *new);
void		ft_error_handling(t_core *core, int flag);
void		init_core(t_core *core);
void		ft_echo_management(t_core *core);
void		ft_exit_management(t_core *core);
void		ft_pwd_management(t_core *core);
void		ft_env_management(t_core *core);
void		ft_export_management(t_core	*core);
void		env_and_exp(t_core	*core);
void		add_to_export(t_core	*core);
void		flush_the_terminal(void);
void		ft_chdir(t_core	*core);
void		add_export_env(t_core	*core);
void		expander(t_core *core);
void		init_list(t_core *g_core);
void		add_export(t_core	*core);
void		print_export(t_core	*core);
void		print_export2(t_core	*core);
void		ft_exec(t_core	*core);
void		add_env(t_core	*core);
int			echo_n_control(t_core *core);
void		ft_access(t_core	*core);
void		ft_builtins(t_core *core);
int			ft_strchr(const char *s, int c);
void		childforexec(t_core *core);
void		ft_redirections(t_core *core);
void		create_file(t_core *core, int mode);
void		heredoc(t_core	*core);
void		input(t_core *core);
void		signal_handler(int sig);
void		init_signal(void);
void		ft_exit_management(t_core *core);
void		leximus(t_core *core);
int			check_operator(t_core *core);
int			control_quote(t_core *core);
int			check_redirection(t_core *core);
int			check_q(t_core *core);
void		init_temp(char	**env, t_core *core);
void		ft_path(t_core	*core);
void		init_list(t_core *g_core);
void		find_err_code(t_core	*core);
int			exit_control(t_core *core);
void		check_q2(t_core	*core);
void		select_type(t_core	*core);
void		pipe_management(t_core	*core);
void		init_main(t_core *g_core, char **env);
void		main_loop(t_core *g_core);
void		arg_control(t_core	*core);
void		heredoc_management(t_core	*c);
void		select_type2(t_core	*core);
void		ft_exit(void);

#endif
