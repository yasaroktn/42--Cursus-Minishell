/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:09:29 by yokten            #+#    #+#             */
/*   Updated: 2023/12/28 08:04:47 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_exit(t_main *main)
{
	if (main->lexer_list->next)
	{
		if (exit_numeric_control(main->lexer_list->next->content))
		{
			if (main->lexer_list->next->next)
				exit_shell(main, 2);
			else
			{
				printf("exit\n");
				exit(ft_atoi(main->lexer_list->next->content));
			}
		}
		else
			exit_shell(main, 1);
	}
	else
		exit_shell(main, 0);
}

int	echo_n_control(t_main *main)
{
	main->a = 1;
	while (main->lexer_list->content[main->a])
	{
		if (main->lexer_list->content[main->a] != 'n')
			return (0);
		main->a++;
	}
	return (1);
}

void	ft_echo(t_main *main)
{
	main->flag = 1;
	if (main->lexer_list->next != NULL)
	{
		main->lexer_list = main->lexer_list->next;
		if (!ft_strncmp(main->lexer_list->content, "-n", 2) \
		&& echo_n_control(main))
			main->flag = 0;
		while (main->lexer_list && \
		!ft_strncmp(main->lexer_list->content, "-n", 2)
			&& echo_n_control(main))
			main->lexer_list = main->lexer_list->next;
		while (main->lexer_list)
		{
			if (main->lexer_list->type == ARGUMENT)
				printf("%s", main->lexer_list->content);
			else if (main->lexer_list->type == PIPE)
				ft_builtin(main);
			main->lexer_list = main->lexer_list->next;
			if (main->lexer_list && main->lexer_list->type == ARGUMENT)
				printf(" ");
		}
	}
	if (main->flag == 1)
		printf("\n");
}

void	ft_cd(t_main	*main)
{
	main->i = 0;
	if (main->lexer_list->next)
		main->lexer_list = main->lexer_list->next;
	if (main->lexer_list && main->lexer_list->type == ARGUMENT)
		main->i = chdir(main->lexer_list->content);
	else if (!main->lexer_list->next)
		main->i = chdir("/Users/yokten");
	else if (main->lexer_list->next && main->lexer_list->next->type == ARGUMENT)
		printf("cd: too many arguments\n");
	ft_change_dir(main);
	if (main->i < 0)
		printf("cd: no such file or directory: %s\n",
			main->lexer_list->content);
	free(main->shell_name);
	main->shell_name = ft_strjoin(main->pwd, " > monkeshell$ ");
	main->i = 0;
}

void	ft_builtin(t_main *main)
{
	if (!ft_strcmp(main->lexer_list->content, "exit") && \
	!main->pipe_count && !main->redir_count)
		ft_exit(main);
	else if (!ft_strcmp(main->lexer_list->content, "echo") && \
	!main->pipe_count && !main->redir_count)
		ft_echo(main);
	else if (!ft_strcmp(main->lexer_list->content, "cd") && \
	!main->pipe_count && !main->redir_count)
		ft_cd(main);
	else if (!ft_strcmp(main->lexer_list->content, "pwd") && \
	!main->pipe_count && !main->redir_count)
		ft_pwd(main);
	else
		ft_builtin2(main);
}
