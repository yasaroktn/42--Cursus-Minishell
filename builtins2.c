/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:44:47 by yokten            #+#    #+#             */
/*   Updated: 2023/11/30 11:54:40 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_pwd_management(t_core	*core)
{
	char	*str;

	str = NULL;
	printf("%s\n", getcwd(str, 0));
	core->pwd = ft_strjoin("\033[0;35m", getcwd(str, 0));
}

void	ft_chdir(t_core	*core)
{
	core->i = 0;
	core->pwd = ft_strjoin("\033[0;35m", getcwd(core->pwd, 0));
	if (core->lexer->next)
		core->lexer = core->lexer->next;
	if (core->lexer && core->lexer->type == 2)
		core->i = chdir(core->lexer->content);
	else if (!core->lexer->next)
		core->i = chdir("/Users/yokten");
	else if (core->lexer->next && core->lexer->next->type == 2)
		printf("cd: too many arguments\n");
	if (core->i < 0)
		printf("cd: no such file or directory: %s\n",
			core->lexer->content);
	core->pwd = ft_strjoin("\033[0;35m", getcwd(core->pwd, 0));
}

void	ft_export_management(t_core	*core)
{
	core->i = 0;
	core->k = 0;
	core->export = core->export_head;
	if (core->lexer->next == NULL || core->lexer->next->type != 2)
	{
		while (core->export)
		{
			core->i++;
			core->export = core->export->next;
		}
		core->export = core->export_head;
		print_export(core);
	}
	else
		add_export_env(core);
}

void	add_export_env(t_core	*core)
{
	core->lexer = core->lexer->next;
	core->l = 0;
	export_lstadd_back(core->export,
		export_listnew(ft_strdup(core->lexer->content)));
	while (core->lexer->content[core->l])
	{
		if (core->lexer->content[core->l] == '=')
		{
			env_lstadd_back(&core->env,
				env_listnew(ft_strdup(core->lexer->content)));
			break ;
		}
		core->l++;
	}
	if (core->lexer->next != NULL && core->lexer->next->type == 2)
		add_export_env(core);
}
