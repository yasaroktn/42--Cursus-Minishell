/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:10:09 by yokten            #+#    #+#             */
/*   Updated: 2023/12/24 03:10:10 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin2(t_main *main)
{
	if (!ft_strcmp(main->lexer_list->content, "export") && \
	!main->pipe_count && !main->redir_count)
		ft_export(main);
	else if (!ft_strcmp(main->lexer_list->content, "unset") && \
	!main->pipe_count && !main->redir_count)
		ft_unset(main);
	else if (!ft_strcmp(main->lexer_list->content, "env") && \
	!main->pipe_count && !main->redir_count)
		ft_env(main);
	else
		ft_exec(main);
}

void	ft_change_dir(t_main *main)
{
	char	*str;

	str = NULL;
	if (main->pwd != NULL)
		free(main->pwd);
	main->pwd = getcwd(str, 0);
}

void	add_export_env(t_main *main)
{
	main->lexer_list = main->lexer_list->next;
	main->l = 0;
	replace_or_add_exp(&main->export_list, main->lexer_list->content);
	while (main->lexer_list->content[main->l])
	{
		if (main->lexer_list->content[main->l] == '=')
		{
			replace_or_add_env(&main->env_list, main->lexer_list->content);
			break ;
		}
		main->l++;
	}
	if (main->lexer_list->next != NULL && \
	main->lexer_list->next->type == ARGUMENT)
		add_export_env(main);
}
