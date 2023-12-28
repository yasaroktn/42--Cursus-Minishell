/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:10:02 by yokten            #+#    #+#             */
/*   Updated: 2023/12/28 05:32:33 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	declare_export(t_main	*main)
{
	printf("declare -x ");
	while (main->export_list->content[main->i])
	{
		printf("%c", main->export_list->content[main->i]);
		if (main->export_list->content[main->i] == '=')
		{
			main->flag = 1;
			printf("%c", 34);
		}
		main->i++;
		if (main->export_list->content[main->i] == '\0' && main->flag == 1)
		{
			printf("%c", 34);
			main->flag = 0;
		}
	}
	main->i = 0;
	main->export_list = main->export_list->next;
	printf("\n");
}

void	ft_unset(t_main *main)
{
	if (main->lexer_list->next)
		main->lexer_list = main->lexer_list->next;
	if (main->lexer_list->content)
	{
		main->tmp_joined = ft_strjoin(main->lexer_list->content, "=");
		delete_node_t_exp(&main->export_head, main->lexer_list->content);
		delete_node_t_env(&main->env_head, main->tmp_joined);
		free(main->tmp_joined);
	}
	if (main->lexer_list->next && main->lexer_list->next->type == ARGUMENT)
		ft_unset(main);
}

int	exit_numeric_control(char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]))
	{
		i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}
