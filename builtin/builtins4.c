/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:10:09 by yokten            #+#    #+#             */
/*   Updated: 2023/12/28 21:42:09 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
	ft_pwd_add(main->env_list, main->pwd);
}

void	ft_pwd_add(t_env *env, char *pwd)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && ft_strncmp(tmp->content, "PWD=", 4))
		tmp = tmp->next;
	if (tmp && tmp->content)
	{
		free(tmp->content);
		tmp->content = NULL;
		tmp->content = ft_strjoin("PWD=", pwd);
	}
}

void	ft_oldpwd_add(t_env *env, char *oldpwd)
{
	t_env	*tmp;
	char	*str;

	str = NULL;
	tmp = env;
	while (tmp && ft_strncmp(tmp->content, "OLDPWD=", 7))
		tmp = tmp->next;
	if (tmp == NULL)
	{
		str = ft_strjoin("OLDPWD=", oldpwd);
		env_lstadd_back(&env, env_listnew(ft_strdup(str)));
		free(str);
		str = NULL;
	}
	else
	{
		free(tmp->content);
		tmp->content = NULL;
		tmp->content = ft_strjoin("OLDPWD=", oldpwd);
	}
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
