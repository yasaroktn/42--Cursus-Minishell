/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:41:40 by yokten            #+#    #+#             */
/*   Updated: 2023/11/21 23:02:23 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		//printf("girdim\n");
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
	//printf("%s\n", res[core->j]);
	arg[0] = core->lexer->content;
	core->i = 1;
	while (core->lexer->next && core->lexer->next->type == 2)
	{
		core->lexer = core->lexer->next;
		arg[core->i] = core->lexer->content;
		core->i++;
	}
	//printf("%s\n", res[core->j]);
	arg[core->i] = NULL;
	core->env = core->env_head;
	core->i = 0;
	while (core->env)
	{
		env2[core->i++] = core->env->content;
		core->env =core->env->next;
	}
	execve(res[core->j], arg, env2);
	printf("%s : command not found\n", core->lexer->content);
}
