/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:41:40 by yokten            #+#    #+#             */
/*   Updated: 2023/11/25 13:21:14 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void execc(t_core *core, char **arg, char **env, int f)
//{
//	int fd[2];
//	int	i;
//	pid_t pid;
//	
//	pipe(fd);
//	pid = fork();
//	if (pid == 0)
//	{
//		if (f == 1)
//			dup2(fd[0], 0);
//		i = 0;
//		while (arg[i])
//		{
//			if(strncmp(arg[i], "|", 1) == 0)
//			{
//				dup2(fd[1], 1);
//				arg[i] = NULL;
//				break ;
//			}	
//		}
//		execve(arg[0], arg, env);
//	}
//	waitpid(pid, NULL, 0);
//	close(fd[0]);
//	close(fd[1]);
//}

void childforexec(t_core *core)
{
	if (core->flag1 == 0)
	{
		pipe(core->pipes);
		core->flag1 = 1;
	}
	if (core->lexer_head || (!ft_strncmp(core->lexer->content, "|", 1) && core->lexer->next->content))
	{
		ft_exec(core);
		core->flag1 = 2;
	}
	if (ft_strncmp(core->lexer->content, "|", 1) == 0)
	{
		core->lexer = core->lexer->next;
		ft_exec(core);
	}
}

void	ft_exec(t_core	*core)
{
	char **res;
	char *slash_content;
	core->i = -1;
	char **arg = malloc(sizeof(char *) * 100);
	char **env2 = malloc(sizeof(char *) * 100);
	core->env = core->env_head;

	while (core->env)
	{
		if (!ft_strncmp(core->env->content,"PATH=", 5))
			break;
		core->env = core->env->next;
	}
	res = ft_split(&core->env->content[5], ':');
	slash_content = ft_strjoin("/",core->lexer->content);

	while(res[++core->i])
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
		core->env =core->env->next;
	}
	pid_t pid = fork();
	if (pid == 0)
	{
		//ORTADA Kİ COMMANDLER İÇİN YAZILACAK
		if (core->flag1 == 2)
		{
			close(core->pipes[1]);
			dup2(core->pipes[0], 0);
			close(core->pipes[0]);
		}
		if (core->lexer->next && core->lexer->next->type == 3)
		{
			close(core->pipes[0]);
			dup2(core->pipes[1], 1);
			close(core->pipes[1]);
		}
		execve(res[core->j], arg, env2);
	}
	waitpid(pid, NULL, 0);
	if (core->lexer->next && core->lexer->next->type == 3 && core->flag2 == 0)
	{
		core->flag2++;
		close(core->pipes[1]);
	}
	//DÜZELTİLECEK
	else if (core->lexer->next && core->lexer->next->type == 3 && core->flag == 1);
	else
		close(core->pipes[0]);
}
