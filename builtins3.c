/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:03:57 by yokten            #+#    #+#             */
/*   Updated: 2023/11/30 12:49:18 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(t_core	*core)
{
	core->env_head = core->env;
	core->i = 0;
	core->env->content = core->tmp[core->i++];
	core->export->next = NULL;
	while (core->tmp[core->i])
	{
		if (core->tmp[core->i])
			env_lstadd_back(&core->env,
				env_listnew(ft_strdup(core->tmp[core->i])));
		if (core->env->next != NULL)
			core->env = core->env->next;
		core->i++;
	}
	core->env = core->env_head;
}

void	ft_env_management(t_core	*core)
{
	core->i = 0;
	core->env = core->env_head;
	while (core->env)
	{
		printf("%s\n", core->env->content);
		core->env = core->env->next;
	}
	core->env = core->env_head;
}

void	ft_exit_management(t_core *core)
{
	core->i = 0;
	if (core->lexer->next != NULL)
		find_err_code(core);
	else
	{
		printf("exit\n");
		exit(0);
	}
}

void	find_err_code(t_core	*core)
{
	core->lexer = core->lexer->next;
	if (!exit_control(core))
	{
		core->err_code = 255;
		printf("exit : %s: numaric argument required\n",
			core->lexer->content);
		exit(0);
	}
	else if (core->lexer->next != NULL && core->lexer->type == 2)
	{
		printf("exit: too many arguments\n");
		core->err_code = 1;
	}
	else if (exit_control(core))
	{
		core->err_code = ft_atoi(core->lexer->content);
		if (core->err_code > 255)
			core->err_code = 255;
		printf("exit\n");
		exit(0);
	}
}
