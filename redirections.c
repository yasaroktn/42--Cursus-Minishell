/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:58:00 by yokten            #+#    #+#             */
/*   Updated: 2023/11/29 16:01:57 by yokten           ###   ########.fr       */
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
	char	*input;

	if (core->flag4)
		close(core->heredoc_fd[0]);
	core->flag4 = 1;
	if (pipe(core->heredoc_fd) == -1)
		perror("heredoc err");
	signal(SIGINT, ft_ctrl);
	while (1)
	{
		input = readline("> ");
		if (core->lexer->next->next && (
				!ft_strncmp(core->lexer->next->next->content, "<<", 2)))
		{
			printf("%s\n", core->lexer->next->content);
			printf(" input : %s\n", input);
			if (!ft_strncmp(core->lexer->next->content, input,
					ft_strlen(core->lexer->next->content)))
			{
				printf("girseydim\n");
				core->lexer = core->lexer->next->next;
			}
			heredoc(core);
			break ;
		}
		if (!input || (!ft_strncmp(input, core->lexer->next->content,
					ft_strlen(core->lexer->next->content))
				&& ft_strlen(input) == ft_strlen(core->lexer->next->content)))
		{
			printf("%s\n", core->lexer->next->content);
			printf("girdim\n");
			free(input);
			break ;
		}
		else
		{
			write(core->heredoc_fd[1], input, ft_strlen(input));
			write(core->heredoc_fd[1], "\n", 1);
			free(input);
		}
	}
}

void	input(t_core *core)
{
	int	fd;

	fd = open(core->lexer->next->content, O_RDONLY, 777);
	if (fd == -1)
	{
		close(fd);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}
