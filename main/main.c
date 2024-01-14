/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:11:11 by yokten            #+#    #+#             */
/*   Updated: 2024/01/14 15:33:44 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	check_quotes(t_main	*main)
{
	int	i;
	int	double_quotes;
	int	single_quotes;

	i = 0;
	double_quotes = 0;
	single_quotes = 0;
	while (main->input[i] != '\0')
	{
		if (single_quotes % 2 == 0 && main->input[i] == '\"')
			double_quotes++;
		if (double_quotes % 2 == 0 && main->input[i] == '\'')
			single_quotes++;
		i++;
	}
	if (double_quotes % 2 != 0 || single_quotes % 2 != 0)
	{
		main->err_no = 258;
		printf("monkeshell: syntax error near unexpected token\n");
		return (0);
	}
	return (1);
}

int	free_main(t_main *main)
{
	lex_lstclear(&main->lexer_head);
	free(main->input);
	main->input = NULL;
	main->pipe_count = 0;
	main->redir_count = 0;
	return (1);
}

void	start_shell(t_main *main)
{
	int		status;

	status = 0;
	while (1)
	{
		reset_main(main);
		main->input = readline(main->shell_name);
		if (!main->input)
			exit(1);
		if (history_check(main))
			add_history(main->input);
		if (main->input == NULL)
			exit(1);
		if (!check_quotes(main))
			free_main(main);
		else
			start_shell2(main, status);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_main	*main;

	(void)argc, (void)argv;
	clean_shell();
	main = malloc(sizeof(t_main));
	if (!main)
		return (0);
	init_main(main);
	init_lists(env, main);
	g_signal = 0;
	init_signal();
	main->shell_name = ft_strjoin(main->pwd, " > monkeshell$ ");
	start_shell(main);
	return (0);
}
