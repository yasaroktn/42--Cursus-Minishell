/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:10:36 by yokten            #+#    #+#             */
/*   Updated: 2023/12/24 03:10:37 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_heredoc(t_main	*main)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (main->lexer_list->next->next && (
				main->lexer_list->next->next->type == REDIRECTION))
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
			ft_strlen(main->lexer_list->next->content)))
	{
		main->lexer_list = main->lexer_list->next->next;
	}
	ft_redirections(main);
	return ;
}
