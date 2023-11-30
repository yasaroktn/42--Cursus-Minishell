/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:13:15 by yokten            #+#    #+#             */
/*   Updated: 2023/11/29 21:10:07 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_handling(t_core *core, int flag)
{
	core->k = core->i - 1;
	core->k--;
	while (core->input[core->k] == ' ' && core->k >= 0)
		core->k--;
	if (core->k == -1)
	{
		flag = 0;
		printf("syntax error near unexpected token `|'\n");
	}
	while (core->input[core->i] == ' ')
		core->i++;
	if (core->input[core->i] == '\0')
	{
		if (flag == 1)
			printf("syntax error near unexpected token `|'\n");
		else if (flag == 3)
			printf("syntax error near unexpected token `newline'\n");
		else if (flag == 4)
			printf ("syntax error near unexpected token `%c'\n",
				core->input[core->k - 1]);
	}
	else if (flag == 2)
		printf ("syntax error near unexpected token `%c'\n",
			core->input[core->i]);
	core->input[core->i] = '\0';
	core->err_code = 258;
}
