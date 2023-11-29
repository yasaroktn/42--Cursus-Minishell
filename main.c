/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:08:49 by yokten            #+#    #+#             */
/*   Updated: 2023/11/29 16:22:08 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flush_the_terminal(void)
{
	printf("\033[001;1H\033[2J");
}

int	main(int argc, char **argv, char **env)
{
	t_core	*g_core;

	flush_the_terminal();
	g_core = malloc(sizeof(t_core));
	init_list(g_core);
	init_temp(env, g_core);
	init_core(g_core);
	init_signal();
	(void)argc;
	(void)argv;
	g_core->default_out = dup(1);
	g_core->readline = ft_strjoin(g_core->pwd, " > monkey :\033[0;37m ");
	while (1)
	{
		init_core(g_core);
		g_core->input = readline(g_core->readline);
		if (!g_core->input)
			exit (1);
		if (g_core->input != NULL)
			add_history(g_core->input);
		if (g_core->input)
		{
			if (!control_quote(g_core))
				printf("Quote Error\n");
			leximus(g_core);
		}
		g_core->flag1 = 0;
		g_core->exec_fd = 0;
		g_core->process_iterator = 0;
		while (g_core->lexer != NULL)
		{
			if (g_core->lexer->type == 1)
				ft_builtins(g_core);
			if (!g_core->lexer || g_core->lexer->next == NULL)
				break ;
			g_core->lexer = g_core->lexer->next;
		}
		for (int i = 0; i < g_core->child + 1; i++)
		{
			wait(g_core->pid);
		}
	}
}
