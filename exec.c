/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:41:40 by yokten            #+#    #+#             */
/*   Updated: 2023/11/24 23:06:07 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void childforexec(t_core *core)
{
	pipe(core->pipes[core->z]);
	core->pid[core->s] = fork();
	if (core->pid[core->s] == -1)
		perror("Wrong pid!");
	else if (core->pid[core->s++] == 0)
		ft_builtins(core);
	waitpid(core->pid[core->s - 1], NULL, 0);
}

void ft_exec(t_core *core)
{
	char **res;
	char *slash_content;
	core->i = -1;
	char **arg = malloc(sizeof(char *) * 100);
	char **env2 = malloc(sizeof(char *) * 100);
	core->env = core->env_head;

	while (core->env)
	{

		if (!ft_strncmp(core->env->content, "PATH=", 5))
			break;
		core->env = core->env->next;
	}
	res = ft_split(&core->env->content[5], ':');
	slash_content = ft_strjoin("/", core->lexer->content);

	while (res[++core->i])
		res[core->i] = ft_strjoin(res[core->i], slash_content);
	core->j = -1;
	while (res[++core->j])
	{
		if (!access(res[core->j], F_OK))
			break;
	}
	arg[0] = core->lexer->content;
	core->i = 1;
	while (core->lexer->next && core->lexer->next->type == 2)
	{
		core->lexer = core->lexer->next;
		arg[core->i] = core->lexer->content;
		core->i++;
	}
	arg[core->i] = NULL;
	core->env = core->env_head;
	core->i = 0;
	while (core->env)
	{
		env2[core->i++] = core->env->content;
		core->env = core->env->next;
	}
	if (core->pid[core->s++] == 0)
	{	
		if (core->lexer->next && core->lexer->next->type == 3 && core->flag1 == 0)
		{
			childforpipe(core, 1);
			core->flag1 = 1;
		}
		else if (core->lexer->next && core->lexer->next->type == 3 && core->flag1 == 1)
		{
			childforpipe(core, 2);
		}
		else
		{
			childforpipe(core, 3);
		}
		execve(res[core->j], arg, env2);
	}
}
