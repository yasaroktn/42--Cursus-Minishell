/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:41:40 by yokten            #+#    #+#             */
/*   Updated: 2023/11/28 22:24:41 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void childforexec(t_core *core)
{
	ft_exec(core);
}

void	ft_exec(t_core	*core)
{
	pid_t pid;
	int io[2];
	pipe(io);
/* 	char *string[] = {"cat", "a.txt", NULL}; */
	pid = fork();
	if (pid == 0)
	{
		if (core->process_iterator != 0)
		{
			dup2(core->exec_fd, 0);
			close(core->exec_fd);
		}
		if (core->process_iterator != core->child)
		{
			dup2(io[1], 1);
			close(core->exec_fd);
		}
		close(io[0]);
		close(io[1]);
/* 		if (!ft_strncmp(core->lexer_head->content, "cat", 3))
		{
			execve("/bin/cat", string, core->env2);
			printf("error\n %s \n %s\n", string[1], string[0]);
		}
		else */
		/* char *yarra = "";
		read(STDIN_FILENO, yarra, 100000);
		printf("%s\n", yarra); */
		ft_access(core);
		execve(core->res[core->j], core->arg, core->env2);
	}
	if (core->process_iterator != 0)
		close(core->exec_fd);
	close(io[1]);
	dup2(core->default_out, 1);
	core->exec_fd = io[0];
	core->process_iterator++;
}

void	ft_access (t_core	*core)
{
	
	char *slash_content;
	core->i = -1;
	core->arg = malloc(sizeof(char *) * 100);
	core->env2 = malloc(sizeof(char *) * 100);
	core->env = core->env_head;

	while (core->env)
	{
		if (!ft_strncmp(core->env->content,"PATH=", 5))
			break;
		core->env = core->env->next;
	}

	core->res = ft_split(&core->env->content[5], ':');
	slash_content = ft_strjoin("/",core->lexer->content);

	while(core->res[++core->i])
		core->res[core->i] = ft_strjoin(core->res[core->i], slash_content);
	core->j = -1;
	
	while (core->res[++core->j])
	{
		if (!access(core->res[core->j], F_OK))
			break;
	}
	if (core->res[core->j] == NULL)
	{
		printf("command not found: %s\n", core->lexer->content);
		exit(1);
	}
	core->arg[0] = core->lexer->content;
	core->i = 1;
	while (core->lexer->next && (core->lexer->next->type == 2 || core->lexer->next->type == 4))
	{
		core->lexer = core->lexer->next;
			if(core->lexer->type == 2)
			{
				core->arg[core->i] = core->lexer->content;
				core->i++;
			}
			if (core->lexer->type == 4)
			{
				//core->lexer = core->lexer_head;
				ft_redirections(core);
				break;
			}
	}
	core->arg[core->i] = NULL;
	core->env = core->env_head;
	core->i = 0;
	while (core->env)
	{
		core->env2[core->i++] = core->env->content;
		core->env =core->env->next;
	}
}