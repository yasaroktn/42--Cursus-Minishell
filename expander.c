/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:03:54 by sisen             #+#    #+#             */
/*   Updated: 2023/11/30 12:33:34 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_core	*core)
{
	core->k = 0;
	while (core->lexer && core->lexer->content[core->k])
	{
		if (core->lexer->content[core->k] == '$')
		{
			core->k++;
			if (getenv(&core->lexer->content[core->k]) == NULL)
				core->lexer->content = "\0";
			else
				core->lexer->content = getenv(&core->lexer->content[core->k]);
			break ;
		}
		core->k++;
	}
}
