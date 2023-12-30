/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarakus <ckarakus@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:10:36 by yokten            #+#    #+#             */
/*   Updated: 2023/12/30 15:18:58 by ckarakus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
	redir_control(main);
}

void	start_heredoc(t_main	*main)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (main->lexer_list->next->next && (
				!ft_strncmp(main->lexer_list->next->next->content, "<<", 2)))
		{
			start_heredoc2(main, input);
			break ;
		}
		if (!input || !ft_strcmp(input, main->lexer_list->next->content))
		{
			free(input);
			return ;
		}
		else
		{
			write(main->heredoc_fd[1], input, ft_strlen(input));
			write(main->heredoc_fd[1], "\n", 1);
			free(input);
		}
	}
}

void	start_heredoc2(t_main	*main, char *input)
{
	if (!ft_strncmp(main->lexer_list->next->content, input,
			ft_strlen(input)))
	{
		main->lexer_list = main->lexer_list->next->next;
	}
	ft_redirections(main);
	return ;
}
