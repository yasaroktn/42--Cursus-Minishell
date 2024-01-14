/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:10:15 by yokten            #+#    #+#             */
/*   Updated: 2024/01/14 15:34:24 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	error_code(t_main	*main)
{
	free(main->lexer_list->content);
	main->lexer_list->content = ft_itoa(main->err_no);
}

int	error_control(t_main	*main)
{
	if (main->lexer_list->content && main->lexer_list->content[0] \
	&& ft_strchr(";?&|", main->lexer_list->content[0]))
	{
		err_syntax(main);
		return (0);
	}
	while (main->lexer_list)
	{
		if (main->lexer_list->type == PIPE && \
		(!main->lexer_list->next || main->lexer_list->next->type == PIPE))
		{
			err_syntax(main);
			return (0);
		}
		if (main->lexer_list->type == REDIR && \
		(!main->lexer_list->next || main->lexer_list->next->type == REDIR))
		{
			err_syntax(main);
			return (0);
		}
		main->lexer_list = main->lexer_list->next;
	}
	return (1);
}

void	start_shell2(t_main	*main, int status)
{
	int	last;

	last = 0;
	if (main->input)
		ft_parser(main);
	main->lexer_list = main->lexer_head;
	if (!error_control(main) && free_main(main))
		return ;
	main->lexer_list = main->lexer_head;
	if (main->lexer_list->type == REDIR)
		first_redir(main);
	while (main->lexer_list != NULL)
	{
		if (main->lexer_list->type == COMMAND)
			ft_builtin(main);
		if (!main->lexer_list || main->lexer_list->next == NULL)
			break ;
		main->lexer_list = main->lexer_list->next;
	}
	while (main->x++ < main->pipe_count + 1)
		if (main->builtinflag == 0 && waitpid(0, &status, 0) == main->pid2)
			last = status;
	main->err_no = last / 256;
	free_main(main);
}

int	err_syntax(t_main *main)
{
	main->err_no = 258;
	printf("monkeshell: syntax error near unexpected token\n");
	return (0);
}

void	err_unexpected(void)
{
	printf("monkeshell: syntax error near unexpected token `newline'\n");
	exit(1);
}
