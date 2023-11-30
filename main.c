/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:08:49 by yokten            #+#    #+#             */
/*   Updated: 2023/11/30 12:37:11 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flush_the_terminal(void)
{
	printf("\033[001;1H\033[2J");
}

void	input(t_core *core)
{
	int	fd;

	fd = open(core->lexer->next->content, O_RDONLY, 777);
	if (fd == -1)
	{
		close(fd);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	init_main(t_core *g_core, char **env)
{
	flush_the_terminal();
	init_list(g_core);
	init_core(g_core);
	init_temp(env, g_core);
	g_core->default_out = dup(1);
}

void	main_loop(t_core *g_core)
{
	init_signal();
	while (1)
	{
		g_core->readline = ft_strjoin(g_core->pwd, " > monkeys 🙉🙊🙈 :\033[0;37m ");
		g_core->input = readline(g_core->readline);
		if (g_core->input == NULL)
		{
			printf("%s exit\n", g_core->pwd);
			exit(1);
		}
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
		while (g_core->lexer && g_core->lexer != NULL)
		{
			//printf("ĞAAAAAAAAAAAAAAH ERRROR ERGİN\n%p\n", g_core->lexer);
			if (g_core->lexer->type == 1)
			{
				ft_builtins(g_core);
			}
			if (!g_core->lexer || g_core->lexer->next == NULL)
			{
				break ;
			}
			g_core->lexer = g_core->lexer->next;
		}
		if (g_core->input != NULL && ft_strlen(g_core->input) > 0)
		{
			//printf("%zu\n%s\n", ft_strlen(g_core->input), g_core->input);
			free(g_core->input);
			free(g_core->readline);
			g_core->input = NULL;
			g_core->readline = NULL;
		}
	}
}

//pipe ve < dışında unexpected token dönmeyecek redirlerden i + 1 varsa fixlenmesi lazım
//echo sonrası seg var
//$?
//1den fazla redir denenmeli
//tırnak kontrolü yap, check_q2 return değer istiyor mu gerçekten sildik ama
//enter sorunu devam ediyor
//readline sorunu, double readline 
//sinyale bi bak
//malloclar calloc yapılacak
//void * sistemi eklenecek
//strdup, strjoin, split ve calloc void*lanacak
//builtinler extra yazıyla da oluyor like echooo pwdd
//env fixlenecek
int	main(int argc, char **argv, char **env)
{
	t_core	*g_core;

	g_core = malloc(sizeof(t_core));
	init_main(g_core, env);
	(void)argc;
	(void)argv;
	main_loop(g_core);
}
