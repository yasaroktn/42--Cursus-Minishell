/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:57:32 by yokten            #+#    #+#             */
/*   Updated: 2023/11/30 11:46:39 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_list(t_core *g_core)
{
	g_core->lexer = malloc(sizeof(t_lexer));
	if (!g_core->lexer)
		exit(0);
	g_core->env = malloc(sizeof(t_env));
	g_core->export = malloc(sizeof(t_export));
}

void	init_temp(char	**env, t_core *core)
{
	core->t = 0;
	while (env[core->t] && env[core->t + 1] && env[core->t] != NULL && env[core->t + 1] != NULL)
		core->t++;
	core->tmp = malloc(sizeof(char *) * (core->t + 1));
	core->t = -1;
	while (env[++core->t])
		core->tmp[core->t] = ft_strdup(env[core->t]);
	core->tmp[core->t] = NULL;
	add_export(core);
	add_env(core);
}

void	init_core(t_core *core)
{
	core->child = 0;
	core->p = 0;
	core->i = 0;
	core->j = 0;
	core->k = 0;
	core->l = 0;
	core->t = 0;
	core->s = 0;
	core->z = -1;
	core->pid = malloc(sizeof(int) * 100);
	core->flag = 0;
	core->flag1 = 0;
	core->flag2 = 0;
	core->flag4 = 0;
	core->flag5 = 0;
	core->lex_flag = 0;
	core->err_code = 0;
	core->exec_fd = 0;
	core->process_iterator = 0;
	core->swap = NULL;
	core->expanded = NULL;
	core->input = NULL;
	core->pwd = ft_strjoin("\033[0;35m", getcwd(core->pwd, 0));
}
