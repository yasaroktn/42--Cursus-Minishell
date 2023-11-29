/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:37:31 by yokten            #+#    #+#             */
/*   Updated: 2023/11/29 16:14:22 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_management(t_core *core)
{
	core->lexer = core->lexer->next;
	if (core->lexer->content)
		core->tmp_joined = ft_strjoin(core->lexer->content, "=");
	core->i = -1;
	while (core->tmp[++core->i])
	{
		if (!ft_strncmp(core->tmp_joined, core->tmp[core->i],
				ft_strlen(core->tmp_joined)))
		{
			while (core->tmp[core->i])
			{
				core->tmp[core->i] = core->tmp[core->i + 1];
				core->i++;
			}
			return ;
		}
	}
}

void	ft_builtins(t_core *core)
{
	const t_functionPointer	function_array[] = {ft_echo_management,
		ft_unset_management, ft_exit_management, ft_pwd_management,
		ft_env_management, ft_chdir, ft_export_management, childforexec};
	int						i;
	const char				*commands[] = {"echo", "unset", "exit",
		"pwd", "env", "cd", "export", NULL};

	core->input = core->lexer->content;
	i = 0;
	while (commands[i] != NULL && ft_strncmp(core->input,
			commands[i], ft_strlen(commands[i])) && i < 7)
		++i;
	function_array[i](core);
}

int	echo_n_control(t_core *core)
{
	core->i = 1;
	while (core->lexer->content[core->i])
	{
		if (core->lexer->content[core->i] != 'n')
			return (0);
		core->i++;
	}
	return (1);
}

void	ft_echo_management(t_core *core)
{
	core->flag = 1;
	if (core->lexer->next != NULL)
	{
		core->lexer = core->lexer->next;
		if (!ft_strncmp(core->lexer->content, "-n", 2) && echo_n_control(core))
			core->flag = 0;
		while (!ft_strncmp(core->lexer->content, "-n", 2)
			&& echo_n_control(core))
			core->lexer = core->lexer->next;
		while (core->lexer)
		{
			if (core->lexer->type == 2)
				printf("%s ", core->lexer->content);
			else if (core->lexer->type == 3)
				ft_builtins(core);
			core->lexer = core->lexer->next;
		}
	}
	if (core->flag == 1)
		printf("\n");
}

int	exit_control(t_core *core)
{
	core->i = 0;
	while (ft_isdigit(core->lexer->content[core->i]))
		core->i++;
	while (core->lexer->content[core->i] == ' ')
		core->i++;
	if (core->lexer->content[core->i] == '\0')
		return (1);
	else
		return (0);
}
