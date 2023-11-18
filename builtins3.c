/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:03:57 by yokten            #+#    #+#             */
/*   Updated: 2023/11/18 07:19:39 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(t_core	*core)
{
	core->env_head = core->env;
	core->i = 0;
	core->env->content = core->tmp[core->i++];
	while (core->tmp[core->i])
	{
		if (core->tmp[core->i + 1])
			env_lstadd_back(&core->env,
				env_listnew(ft_strdup(core->tmp[core->i])));
		if (core->env->next != NULL)
			core->env = core->env->next;
		core->i++;
	}
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
}