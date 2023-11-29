/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leximus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:16:13 by yokten            #+#    #+#             */
/*   Updated: 2023/11/29 16:19:15 by yokten           ###   ########.fr       */
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
			return (0);
		core->i++;
	}
	return (1);
}

void	leximus(t_core *core)
{
	core->lexer_head = core->lexer;
	core->flag = 1;
	core->i = 0;
	core->j = 0;
	while (core->input[core->i])
	{
		while (core->input[core->i] == ' ')
			core->i++;
		if (core->input[core->i] == '|')
		{
			core->child++;
			core->lexer->type = 3;
			core->flag = 1;
			core->lexer->content = malloc(sizeof(char) * 2);
			core->lexer->content[core->j] = core->input[core->i];
			core->lexer->content[++core->j] = '\0';
			core->i++;
		}
		else if (core->input[core->i] == '<' || core->input[core->i] == '>')
		{
			core->lexer->type = 4;
			check_redirection(core);
		}
		else if (core->input[core->i] == 34 || core->input[core->i] == 39)
		{
			check_q(core);
			if (core->flag == 1)
			{
				core->lexer->type = 1;
				core->flag = 0;
			}
			else
				core->lexer->type = 2;
		}
		else
		{
			core->k = core->i;
			core->j = 0;
			if (core->flag == 1)
			{
				core->lexer->type = 1;
				core->flag = 0;
			}
			else
				core->lexer->type = 2;
			while (check_operator(core))
				core->i++;
			core->lexer->content = malloc(sizeof(char) * \
					(core->i - core->k + 1));
			core->i = core->k;
			while (check_operator(core))
			{
				if ((core->input[core->i] == 34)
					|| (core->input[core->i] == 39))
					core->i++;
				else
				{
					core->lexer->content[core->j] = core->input[core->i];
					core->j++;
					core->i++;
				}
			}
			core->lexer->content[core->j] = '\0';
			expander(core);
		}
		while (core->input[core->i] == ' ')
			core->i++;
		if (core->input[core->i] != '\0')
		{
			lexer_lstadd_back(&core->lexer_head,
				lexer_listnew(ft_strdup(core->lexer->content)));
		}
		core->j = 0;
		if (core->input[core->i] != '\0')
			core->lexer = core->lexer->next;
	}
	core->lexer = core->lexer_head;
}
