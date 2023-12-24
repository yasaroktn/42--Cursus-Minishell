/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:11:32 by yokten            #+#    #+#             */
/*   Updated: 2023/12/24 07:45:40 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

enum e_TYPE
{
	PIPE = 1,
	COMMAND,
	ARGUMENT,
	REDIR
};

int		g_signal;
void	clean_shell(void);
int		history_check(t_main *main_struct);
void	ft_parser(t_main *main_struct);
void	init_main(t_main *main);
void	pipe_manage(t_main *main);
void	redir_manage(t_main *main);
void	ft_parser(t_main *main);
t_lexer	*lex_listnew(char *content);
void	lex_lstadd_back(t_lexer **lst, t_lexer *new);
void	lex_lstclear(t_lexer **lst);
char	*ft_string_join(char const *s1, char const *s2);
void	dollar_manage(char *string, t_main *main);
char	*ft_strdup2(const char *s1);
char	*ft_substring(char const *s, unsigned int start, size_t len);
void	normal_manage(t_main *main);
void	ft_builtin(t_main *main);
void	single_quote_manage(t_main *main);
void	double_quote_manage(t_main *main);
void	normal_dollar_manage(char	*str, t_main	*main);
char	*split_dolar_or_space(char *string, t_main *main);
int		ft_strcmp(const char *s1, const char *s2);
void	exit_shell(t_main	*main, int flag);
void	ft_echo(t_main *main);
void	ft_pwd(t_main *main);
void	ft_cd(t_main	*main);
void	init_lists(char **env, t_main *main);
t_env	*env_listnew(char *content);
void	env_lstadd_back(t_env **lst, t_env *new);
t_exp	*export_listnew(char *content);
void	export_lstadd_back(t_exp **lst, t_exp *new);
void	add_export(t_main	*main);
void	add_env(t_main	*main);
void	ft_env(t_main *main);
void	print_export(t_main	*main);
void	ft_export(t_main *main);
void	add_export_env(t_main	*main);
void	declare_export(t_main	*main);
void	ft_exec(t_main	*main);
void	ft_exit(t_main	*main);
void	ft_access(t_main *main);
void	reset_main(t_main *main);
void	ft_unset(t_main *main);
void	delete_node_t_exp(t_exp **t_exp, char *content);
void	delete_node_t_env(t_env **t_env, char *content);
void	parse_path(t_main *main);
void	create_arg(t_main *main);
int		count_args(t_main *main);
void	child_process(t_main *main);
void	ft_redirections(t_main *main);
void	input(t_main *main);
void	create_file(t_main *main, int mode);
void	ft_builtin2(t_main *main);
void	heredoc(t_main	*main);
void	redir_manage2(t_main *main);
int		error_control(t_main *main);
int		check_quotes(t_main	*main);
void	signal_handler(int sig);
void	init_signal(void);
void	error_code(t_main	*main);
void	start_shell2(t_main	*main, int status);
void	start_heredoc(t_main	*main);
void	free_main(t_main *main);
void	start_heredoc2(t_main	*main, char *input);
int		exit_numeric_control(char *str);
void	ft_change_dir(t_main *main);
void	replace_or_add_env(t_env **list, char *content);
void	replace_or_add_exp(t_exp **list, char *content);
void	add_export_env(t_main *main);
void	parse_path2(t_main *main, char *slash_content);
void	parse_path3(t_main *main);
void	replace_or_add_env(t_env **list, char *content);
void	replace_or_add_exp(t_exp **list, char *content);
int		err_syntax(t_main *main);
void	dollar_manage3(t_main *main, char *string);
void	err_unexpected(void);
void	copy_env(t_main *main);

#endif