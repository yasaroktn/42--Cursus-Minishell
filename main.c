/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:08:49 by yokten            #+#    #+#             */
/*   Updated: 2023/11/25 12:18:35 by yokten           ###   ########.fr       */
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
	while (env[core->t])
		core->t++;
	core->tmp = malloc(sizeof(char *) * (core->t + 1));
	core->t = -1;
	while (env[++core->t])
		core->tmp[core->t] = ft_strdup(env[core->t]);
	core->tmp[core->t] = NULL;
	add_export(core);
	add_env(core);
}

int	check_redirection(t_core *core)
{
	int	a;

	a = core->i;
	if ((core->input[core->i] == '<' && core->input[core->i + 1] != '>')
		|| (core->input[core->i] == '>' && core->input[core->i + 1] != '<'))
		core->i += 1;
	if (core->input[core->i] == core->input[core->i - 1])
		core->i += 1;
	if (a == core->i - 2 && core->input[core->i] == core->input[core->i - 1])
		core->i--;
	else if (a < core->i)
	{
		core->lexer->content = malloc(sizeof(char) * (core->i - a + 1));
		while (a <= core->i)
			core->lexer->content[core->j++] = core->input[a++];
		core->i++;
		return (1);
	}
	return (0);
}

int	check_Q(t_core *core)
{
	if (core->input[core->i] == 34)
	{
		core->i++;
		core->k = core->i;
		while (core->input[core->i] != 34 && core->input[core->i])
			core->i++;
		core->lexer->content = malloc(sizeof(char) * (core->i - core->k + 1));
		core->i = core->k;
		while (core->input[core->i] != 34 && core->input[core->i])
		{
			core->lexer->content[core->j] = core->input[core->i];
			core->i++;
			core->j++;
		}
		core->lexer->content[core->j] = '\0';
		expander(core);
		if (core->input[core->i] != 34)
			return (0);
		core->i++;
	}
	else if (core->input[core->i] == 39)
	{
		core->j = 0;
		core->i++;
		core->k = core->i;
		while (core->input[core->i] != 34 && core->input[core->i])
			core->i++;
		core->lexer->content = malloc(sizeof(char) * (core->i - core->k + 1));
		core->i = core->k;
		while (core->input[core->i] != 39 && core->input[core->i])
		{
			core->lexer->content[core->j] = core->input[core->i];
			core->lexer->content[core->j] = core->input[core->i];
			core->i++;
			core->j++;
		}
		if (core->input[core->i] != 39)
			return (0);
		core->i++;
	}
	return (1);
}

int	check_operator(t_core *core)
{
	if (core->input[core->i] && core->input[core->i] != ' '
		&& core->input[core->i] != '|' && core->input[core->i] != '<'
		&& core->input[core->i] != '>')
		return (1);
	else
		return (0);
}

int	control_quote(t_core *core)
{
	core->i = 0;
	core->control34 = 0;
	core->control39 = 0;
	while (core->input[core->i])
	{
		if (core->input[core->i] == 34 && core->control39 % 2 == 0)
			core->control34++;
		if (core->input[core->i] == 39 && core->control34 % 2 == 0)
			core->control39++;
		core->i++;
	}
	if (core->control34 % 2 == 1 || core->control39 % 2 == 1)
		return (0);
	return (1);
}

void	leximus(t_core *core)
{
	core->lexer_head = core->lexer;
	core->flag = 1;
	core->i = 0;
	core->j = 0;
	while (core->input[core->i])
	{
		while (core->input[core->i] == ' ')
			core->i++;
		if (core->input[core->i] == '|')
		{
			core->child++;
			core->lexer->type = 3;
			core->flag = 1;
			core->lexer->content = malloc(sizeof(char) * 2);
			core->lexer->content[core->j] = core->input[core->i];
			core->lexer->content[++core->j] = '\0';
			core->i++;
		}
		else if (core->input[core->i] == '<' || core->input[core->i] == '>')
		{
			core->lexer->type = 3;
			core->flag = 1;
		}
		else if (core->input[core->i] == 34 || core->input[core->i] == 39)
		{
			check_Q(core);
			if (core->flag == 1)
			{
				core->lexer->type = 1;
				core->flag = 0;
			}
			else
				core->lexer->type = 2;
		}
		else
		{
			core->k = core->i;
			core->j = 0;
			if (core->flag == 1)
			{
				core->lexer->type = 1;
				core->flag = 0;
				
			}
			else
				core->lexer->type = 2;
			while (check_operator(core))
				core->i++;
			
			core->lexer->content = malloc(sizeof(char) * \
					(core->i - core->k + 1));
			core->i = core->k;
			while (check_operator(core))
			{

				if ((core->input[core->i] == 34)
					|| (core->input[core->i] == 39))
					core->i++;
				else
				{
					core->lexer->content[core->j] = core->input[core->i];
					core->j++;
					core->i++;
				}
			}
			core->lexer->content[core->j] = '\0';
			expander(core);

		}
		while (core->input[core->i] == ' ')
			core->i++;
		if (core->input[core->i] != '\0')
		{
			lexer_lstadd_back(&core->lexer_head,
				lexer_listnew(ft_strdup(core->lexer->content)));

		}
		core->j = 0;

		if (core->input[core->i] != '\0')
			core->lexer = core->lexer->next;
	}
	core->lexer = core->lexer_head;
}

void	flush_the_terminal(void)
{
	printf("\033[001;1H\033[2J");
}

// fix the seg of third
// mallocların hepsi calloc olacak
// seri readline kullanımı seggy fucky
//export =tirsiz eklemeyi düzelt
int	main(int argc, char **argv, char **env)
{
	t_core	*g_core;
	flush_the_terminal();
	g_core = malloc(sizeof(t_core));
	init_list(g_core);
	init_core(g_core);
	init_temp(env, g_core);
	(void)argc;
	(void)argv;
	g_core->readline = ft_strjoin(g_core->pwd, " > monkeys 🙉🙊🙈 :\033[0;37m ");
	while (1)
	{
		g_core->input = readline(g_core->readline);
		if (g_core->input != NULL)
			add_history(g_core->input);
		if (g_core->input)
		{
			if (!control_quote(g_core))
				printf("tırnak hatası");
			leximus(g_core);
		}
		g_core->flag1 = 0;
		while (g_core->lexer != NULL)
		{
			if (g_core->lexer->type == 1)
				ft_builtins(g_core);
			if (g_core->lexer->next == NULL)
				break ;
			g_core->lexer = g_core->lexer->next;
		}
	}
}