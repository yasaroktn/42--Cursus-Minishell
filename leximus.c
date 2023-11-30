/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leximus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:16:13 by yokten            #+#    #+#             */
/*   Updated: 2023/11/30 12:36:30 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		select_type(core);
		while (core->input[core->i] == ' ')
			core->i++;
		if (core->input[core->i] != '\0')
		{
			printf("\nanan ana nan ana nanana batmaaaan\n");
			lexer_lstadd_back(&core->lexer_head,
				lexer_listnew(ft_strdup(core->lexer->content)));
		}
		core->j = 0;
		if (core->input[core->i] != '\0')
			core->lexer = core->lexer->next;
	}
	core->lexer = core->lexer_head;
}

void	select_type(t_core	*core)
{
	if (core->input[core->i] == '|')
	{
		pipe_management(core);
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
		select_type2(core);
		expander(core);
		if (core->lexer)
			core->lexer->content[core->j] = '\0';
	}
}

void	pipe_management(t_core	*core)
{
	core->child++;
	core->lexer->type = 3;
	core->flag = 1;
	core->lexer->content = malloc(sizeof(char) * 2);
	core->lexer->content[core->j] = core->input[core->i];
	core->lexer->content[++core->j] = '\0';
	core->i++;
}

void	select_type2(t_core	*core)
{
	core->k = core->i;
	core->j = 0;
	if (core->flag == 1 && core->lexer)
	{
		core->lexer->type = 1;
		core->flag = 0;
	}
	else if (core->lexer)
	{
		core->lexer->type = 2;
	}
	while (check_operator(core))
		core->i++;
	if (core->lexer)
	{
		core->lexer->content = malloc(sizeof(char) * \
				(core->i - core->k + 1));
	}
	core->i = core->k;
	while (check_operator(core) && core->lexer)
	{
		if ((core->input[core->i] == 34)
			|| (core->input[core->i] == 39))
			core->i++;
		else
		{
			core->lexer->content[core->j] = core->input[core->i++];
			core->j++;
		}
	}
}
