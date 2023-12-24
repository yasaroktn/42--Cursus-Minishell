/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:11:59 by yokten            #+#    #+#             */
/*   Updated: 2023/12/24 03:12:00 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirections(t_main *main)
{
	main->q = 0;
	if ((!ft_strcmp(main->lexer_list->content, ">>")))
		create_file(main, 1);
	else if (!ft_strcmp(main->lexer_list->content, ">"))
		create_file(main, 2);
	if ((!ft_strcmp(main->lexer_list->content, "<<")))
		heredoc(main);
	else if (!ft_strcmp(main->lexer_list->content, "<"))
	{
		input(main);
	}
}

void	create_file(t_main *main, int mode)
{
	int		fd;

	fd = 0;
	if (!main->lexer_list->next)
		err_unexpected();
	else if (mode == 2)
		fd = open(main->lexer_list->next->content, O_CREAT
				| O_WRONLY | O_TRUNC, 0777);
	else if (mode == 1)
		fd = open(main->lexer_list->next->content, O_CREAT
				| O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		close(fd);
		printf("Cannot create file\n");
		exit (1);
	}
	dup2(fd, 1);
	close(fd);
	if (main->lexer_list->next->next)
	{
		main->lexer_list = main->lexer_list->next->next;
		ft_redirections(main);
	}
}

void	input(t_main *main)
{
	int	fd;

	if (!main->lexer_list->next)
	{
		printf("monkeshell: syntax error near unexpected token `newline'\n");
		exit(1);
	}
	fd = open(main->lexer_list->next->content, O_RDONLY, 777);
	if (fd == -1)
	{
		close(fd);
		printf("%s: No such file or directory\n", \
		main->lexer_list->next->content);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (main->lexer_list->next->next)
	{
		main->lexer_list = main->lexer_list->next->next;
		ft_redirections(main);
	}
}

void	ft_ctrl(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		printf("\n");
		exit(1);
	}
}

void	heredoc(t_main	*main)
{
	if (!main->lexer_list->next)
	{
		printf("monkeshell: syntax error near unexpected token `newline'\n");
		exit(1);
	}
	else if (main->heredoc_flag)
		close(main->heredoc_fd[0]);
	main->heredoc_flag = 1;
	signal(SIGINT, ft_ctrl);
	if (pipe(main->heredoc_fd) == -1)
		perror("heredoc err");
	g_signal = 2;
	start_heredoc(main);
}
