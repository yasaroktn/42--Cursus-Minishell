/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisen <sisen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:03:54 by sisen             #+#    #+#             */
/*   Updated: 2023/11/16 21:39:51 by sisen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_core	*core)
{
	core->k = 0;
	core->expander = getenv(core->lexer->content); 
	printf("%s\n", core->expander);
}

/*void	expander(t_core *core)
{
	char	*res;

	core->i = 0;
	core->expander = core->lexer->content;
	while (core->env[core->i])
	{
		res = ft_split(core->env[core->i], '=')[0];
			printf("d\n");	
		if (!ft_strncmp(core->expander, res, ft_strlen(core->expander)) && \
			ft_strlen(core->expander) == ft_strlen(res))
			{
			printf("c\n");	
				core->lexer->content = ft_split(core->lexer->, '=')[1];
			printf("b\n");	
			}
		else
		{
			core->lexer->content = ft_strdup("");
			printf("a\n");	
	
		}
		printf("f\n");
		core->i++;
	}
}*/
