/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:11:40 by yokten            #+#    #+#             */
/*   Updated: 2023/12/24 06:27:30 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_manage(t_main *main)
{
	main->pipe_count++;
	main->lexer_list->type = PIPE;
	main->parse_flag = 1;
	main->lexer_list->content = ft_strdup("|");
	main->i++;
}

void	redir_manage(t_main *main)
{
	main->redir_count++;
	main->lexer_list->type = REDIR;
	if (!ft_strncmp(&main->input[main->i], ">>", 2))
	{
		main->lexer_list->content = ft_strdup(">>");
		main->i += 2;
	}
	else if (!ft_strncmp(&main->input[main->i], ">", 1))
	{
		main->lexer_list->content = ft_strdup(">");
		main->i++;
	}
	else
		redir_manage2(main);
}

void	single_quote_manage(t_main *main)
{
	main->i++;
	while (main->input[main->i] != '\'')
	{
		main->lexer_list->content = ft_string_join(main->lexer_list->content, \
		ft_substr(main->input, main->i, 1));
		main->i++;
	}
	main->i++;
}

void	double_quote_manage(t_main *main)
{
	main->dollar = main->i;
	main->i++;
	if (main->lexer_list->content == NULL)
	{
		main->dq_temp = ft_strdup("");
		main->lexer_list->content = ft_strdup("");
	}
	else
		main->dq_temp = ft_strdup(main->lexer_list->content);
	while (main->input[main->i] != '\"')
	{
		main->dq_temp = \
		ft_string_join(main->dq_temp, \
		ft_substr(main->input, main->i, 1));
		main->i++;
	}
	main->temp_string = ft_substr \
	(main->input, main->dollar + 1, main->i - main->dollar - 1);
	dollar_manage(main->temp_string, main);
	main->i++;
	free(main->dq_temp);
}

void	ft_parser(t_main *main)
{
	main->lexer_list = lex_listnew(NULL);
	main->lexer_head = main->lexer_list;
	main->parse_flag = 1;
	while (main->input[main->i])
	{
		while (main->input[main->i] == ' ')
			main->i++;
		if (main->input[main->i] == '|')
			pipe_manage(main);
		else if (main->input[main->i] == '<' || main->input[main->i] == '>')
			redir_manage(main);
		else
			normal_manage(main);
		while (main->input[main->i] == ' ')
			main->i++;
		if (main->input[main->i] != '\0')
		{
			lex_lstadd_back(&main->lexer_list, lex_listnew(NULL));
			main->lexer_list = main->lexer_list->next;
		}
	}
	main->i = 0;
}
