/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:41:40 by yokten            #+#    #+#             */
/*   Updated: 2023/11/30 12:14:17 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	ft_exec(t_core	*core)
{
	core->i = 0;
	/* pid_t	pid;

	pipe(core->fd);
	pid = fork();
	if (pid == 0)
		childforexec(core);
	else
	{
		waitpid(pid, NULL, 0);
		core->flag5 = 0;
		if (core->process_iterator != 0)
			close(core->exec_fd);
		dup2(STDOUT_FILENO, core->fd[1]);
		close(core->fd[1]);
		core->exec_fd = core->fd[0];
		core->process_iterator++;
	} */
}

void	childforexec(t_core	*core)
{
	core->flag5 = 1;
	if (core->process_iterator != 0)
	{
		dup2(core->exec_fd, 0);
		close(core->exec_fd);
	}
	if (core->process_iterator != core->child)
	{
		dup2(core->fd[1], 1);
		close(core->exec_fd);
	}
	close(core->fd[0]);
	close(core->fd[1]);
	ft_access(core);
	clear_history();
	if (!ft_strncmp(core->lexer->content, "<<", 2))
	{
		dup2(core->heredoc_fd[0], STDIN_FILENO);
		close(core->heredoc_fd[1]);
	}
	execve(core->res[core->j], core->arg, core->env2);
}

void	ft_access(t_core *core)
{
	core->i = -1;
	core->arg = malloc(sizeof(char *) * 100);
	core->env2 = malloc(sizeof(char *) * 100);
	core->env = core->env_head;
	ft_path(core);
	arg_control(core);
	core->env = core->env_head;
	core->i = 0;
	while (core->env)
	{
		core->env2[core->i++] = core->env->content;
		core->env = core->env->next;
	}
}

void	ft_path(t_core	*core)
{
	while (core->env)
	{
		if (!ft_strncmp(core->env->content, "PATH=", 5))
			break ;
		core->env = core->env->next;
	}
	core->res = ft_split(&core->env->content[5], ':');
	core->s_content = ft_strjoin("/", core->lexer->content);
	while (core->res[++core->i])
		core->res[core->i] = ft_strjoin(core->res[core->i], core->s_content);
	core->j = -1;
	while (core->res[++core->j])
	{
		if (!access(core->res[core->j], F_OK))
			break ;
	}
	if (core->res[core->j] == NULL)
	{
		printf("command not found: %s\n", core->lexer->content);
		exit(1);
	}
}

void	arg_control(t_core	*core)
{
	core->arg[0] = core->lexer->content;
	core->i = 1;
	while (core->lexer->next && (core->lexer->next->type == 2
			|| core->lexer->next->type == 4))
	{
		core->lexer = core->lexer->next;
		if (core->lexer->type == 2)
		{
			core->arg[core->i] = core->lexer->content;
			core->i++;
		}
		if (core->lexer->type == 4)
		{
			ft_redirections(core);
			break ;
		}
	}
	core->arg[core->i] = NULL;
}
