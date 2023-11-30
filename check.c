/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:40:56 by yokten            #+#    #+#             */
/*   Updated: 2023/11/29 21:14:56 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_redirection(t_core *core)
{
	int	a;

	a = core->i;
	if (!ft_strncmp(&core->input[core->i], ">>", 2))
		core->i += 2;
	else if (!ft_strncmp(&core->input[core->i], ">", 1))
		core->i += 1;
	else if (!ft_strncmp(&core->input[core->i], "<<", 2))
		core->i += 2;
	else if (!ft_strncmp(&core->input[core->i], "<", 1))
		core->i += 1;
	if (a < core->i)
	{
		core->lexer->content = malloc(sizeof(char) * (core->i - a + 1));
		while (a <= core->i)
			core->lexer->content[core->j++] = core->input[a++];
		core->i++;
		return (1);
	}
	return (0);
}

int	check_q(t_core *core)
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
		check_q2(core);
	return (1);
}

void	check_q2(t_core	*core)
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
		return ;
	core->i++;
}
