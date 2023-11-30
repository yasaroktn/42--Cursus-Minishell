/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:03:04 by yokten            #+#    #+#             */
/*   Updated: 2023/11/29 17:34:50 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_core	*core)
{
	core->flag = 0;
	while (0 < --core->i)
	{
		while (core->export->next)
		{
			if (core->export->content[0] > core->export->next->content[0])
			{
				core->e_tmp = core->export->next->content;
				core->export->next->content = core->export->content;
				core->export->content = core->e_tmp;
			}
			core->export = core->export->next;
		}
		core->export = core->export_head;
	}
	print_export2(core);
}

void	print_export2(t_core	*core)
{
	core->i = 0;
	while (core->export)
	{
		printf("declare -x ");
		while (core->export->content[core->i])
		{
			printf("%c", core->export->content[core->i]);
			if (core->export->content[core->i] == '=')
			{
				core->flag = 1;
				printf("%c", 34);
			}
			core->i++;
			if (core->export->content[core->i] == '\0' && core->flag == 1)
			{
				printf("%c", 34);
				core->flag = 0;
			}
		}
		core->i = 0;
		core->export = core->export->next;
		printf("\n");
	}
}
