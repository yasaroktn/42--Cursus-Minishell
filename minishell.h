/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:03:17 by yokten            #+#    #+#             */
/*   Updated: 2023/11/27 13:46:31 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "structs.h"
# include "libft/libft.h"

t_lexer	*lexer_listnew(char *content);
t_lexer	*lexer_lstlast(t_lexer *lst);
t_env	*env_listnew(char *content);
t_export	*export_listnew(char *content);
void	ft_unset_management(t_core *core);
void	lexer_lstadd_back(t_lexer **lst, t_lexer *new);
void	env_lstadd_back(t_env **lst, t_env *new);
void	export_lstadd_back(t_export **lst, t_export *new);
void	ft_error_handling(t_core *core, int flag);
void	init_core(t_core *core);
void	ft_echo_management(t_core	*core);
void	ft_exit_management(t_core	*core);
void	ft_pwd_management(t_core	*core);
void	ft_env_management(t_core	*core);
void	ft_export_management(t_core	*core);
void	env_and_exp(t_core	*core);
void	add_to_export(t_core	*core);
void	flush_the_terminal(void);
void	ft_chdir(t_core	*core);
void	add_export_env(t_core	*core);
void	expander(t_core *core);
void	init_list(t_core *g_core);
void	add_export (t_core	*core);
void	print_export(t_core	*core);
void	ft_exec(t_core	*core);
void	add_env(t_core	*core);
int		echo_n_control(t_core *core);
void	ft_access (t_core	*core);
void	ft_builtins(t_core *core);
int		ft_strchr(const char *s, int c);
void    childforexec(t_core *core);
void 	ft_redirections(t_core *core);
//void 	create_file(t_core *core)
//void 	delete_file(t_core *core)

//void    childforpipe(t_core *core, int flag);
#endif


// 954e4a17b4f63bdb8f9db5dab05a0c3bfad61bb6 