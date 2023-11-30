/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:58:00 by yokten            #+#    #+#             */
/*   Updated: 2023/11/29 18:30:48 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirections(t_core *core)
{
	core->l = 0;
	if ((!ft_strncmp(core->lexer->content, ">>", 2)))
		create_file(core, 1);
	else if (!ft_strncmp(core->lexer->content, ">", 1))
		create_file(core, 2);
	else if ((!ft_strncmp(core->lexer->content, "<<", 2)))
		heredoc(core);
	else if (!ft_strncmp(core->lexer->content, "<", 1))
		input(core);
}

void	create_file(t_core *core, int mode)
{
	int		fd;

	fd = 0;
	if (mode == 2)
		fd = open(core->lexer->next->content, O_CREAT
				| O_WRONLY | O_TRUNC, 0777);
	else if (mode == 1)
		fd = open(core->lexer->next->content, O_CREAT
				| O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("minishell");
	}
	dup2(fd, 1);
	close(fd);
}

void	ft_ctrl(int signal)
{
	printf("\n");
	(void)signal;
	exit(errno);
}

void	heredoc(t_core	*core)
{
	if (core->flag4)
		close(core->heredoc_fd[0]);
	core->flag4 = 1;
	if (pipe(core->heredoc_fd) == -1)
		perror("heredoc err");
	signal(SIGINT, ft_ctrl);
	while (1)
		heredoc_management(core);
}

void	heredoc_management(t_core	*c)
{
	c->h_input = readline("> ");
	if (c->lexer->next->next && (
			!ft_strncmp(c->lexer->next->next->content, "<<", 2)))
	{
		if (!ft_strncmp(c->lexer->next->content, c->h_input,
				ft_strlen(c->lexer->next->content)))
		{
			c->lexer = c->lexer->next->next;
		}
		heredoc(c);
		return ;
	}
	if (!c->h_input || (!ft_strncmp(c->h_input, c->lexer->next->content,
				ft_strlen(c->lexer->next->content))
			&& ft_strlen(c->h_input) == ft_strlen(c->lexer->next->content)))
	{
		free(c->h_input);
		return ;
	}
	else
	{
		write(c->heredoc_fd[1], c->h_input, ft_strlen(c->h_input));
		write(c->heredoc_fd[1], "\n", 1);
		free(c->h_input);
	}
}
