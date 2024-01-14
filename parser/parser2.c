/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:11:46 by yokten            #+#    #+#             */
/*   Updated: 2024/01/14 11:55:25 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	dollar_manage(char *string, t_main *main)
{
	char	*tmp;

	while (string[++main->a])
	{
		if (!ft_strcmp(string, "$?"))
			error_code(main);
		else if (string[main->a] == '$')
		{
			tmp = split_dolar_or_space(string, main);
			if (ft_getenv(tmp, main) == NULL)
				ft_memset(&main->lexer_list->content[main->i - 1], '\0', 1);
			else if (ft_getenv(tmp, main) != NULL)
			{
				main->tmp = ft_strdup(ft_getenv(tmp, main));
				main->lexer_list->content = ft_string_join \
				(main->lexer_list->content, main->tmp);
			}
			free(tmp);
		}
		else
			dollar_manage3(main, string);
	}
	free(string);
	main->a = -1;
}

void	normal_dollar_manage(char	*str, t_main	*main)
{
	if (!ft_strcmp(str, "?"))
		error_code(main);
	else if (1 && (main->tmp = ft_getenv(str, main)))
	{
		main->tmp = ft_strdup(ft_getenv(str, main));
		main->lexer_list->content = ft_string_join \
		(ft_substring(main->lexer_list->content, 0, main->i - 1), main->tmp);
	}
	else
	{
		if (main->lexer_list->content == NULL)
			main->lexer_list->content = ft_strdup("");
	}
	free(str);
}

void	no_quote_dollar_manage(t_main *main)
{
	main->i++;
	main->tmp = ft_strdup("");
	while (main->input[main->i] != ' ' && main->input[main->i] != '\0')
	{
		main->tmp = ft_string_join \
		(main->tmp, ft_substr(main->input, main->i, 1));
		main->i++;
	}
	normal_dollar_manage(main->tmp, main);
}

void	normal_manage(t_main *main)
{
	if (main->parse_flag == 1)
	{
		main->lexer_list->type = COMMAND;
		main->parse_flag = 0;
	}
	else
		main->lexer_list->type = ARGUMENT;
	while (main->input[main->i] != ' ' && main->input[main->i] != '\0' && \
	main->input[main->i] != '|' && main->input[main->i] != '>' && \
	main->input[main->i] != '<')
	{
		if (main->input[main->i] == '\'')
			single_quote_manage(main);
		else if (main->input[main->i] == '\"')
			double_quote_manage(main);
		else if (main->input[main->i] == '$')
			no_quote_dollar_manage(main);
		else
		{
			main->lexer_list->content = ft_string_join \
			(main->lexer_list->content, ft_substr(&main->input[main->i], 0, 1));
			main->i++;
		}
	}
}

void	redir_manage2(t_main	*main)
{
	if (!ft_strncmp(&main->input[main->i], "<<", 2))
	{
		main->lexer_list->content = ft_strdup("<<");
		main->i += 2;
	}
	else if (!ft_strncmp(&main->input[main->i], "<", 1))
	{
		main->lexer_list->content = ft_strdup("<");
		main->i++;
	}
}
