/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:10:29 by yokten            #+#    #+#             */
/*   Updated: 2023/12/28 07:50:24 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	child_process(t_main *main)
{
	if (main->process_iterator != 0)
	{
		dup2(main->exec_fd, 0);
		close(main->exec_fd);
	}
	if (main->process_iterator != main->pipe_count)
	{
		dup2(main->io[1], 1);
		close(main->exec_fd);
	}
	close(main->io[0]);
	close(main->io[1]);
	ft_access(main);
	clear_history();
	if (!ft_strncmp(main->lexer_list->content, "<<", 2))
	{
		dup2(main->heredoc_fd[0], STDIN_FILENO);
		close(main->heredoc_fd[1]);
	}
	execve(main->res[main->k], main->arg, main->env2);
	exit(0);
}

void	parse_path2(t_main *main, char *slash_content)
{
	main->res = ft_split(&main->env_list->content[5], ':');
	slash_content = ft_strjoin("/", main->lexer_list->content);
	while (main->res[++main->z])
		main->res[main->z] = ft_strjoin(main->res[main->z], slash_content);
}

void	parse_path3(t_main *main)
{
	if (ft_strcmp(main->lexer_list->content, "exit") || \
	!main->lexer_list->content[0])
		printf("command not found: %s\n", main->lexer_list->content);
	exit(127);
}
