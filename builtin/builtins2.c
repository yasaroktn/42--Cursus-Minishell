/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:09:41 by yokten            #+#    #+#             */
/*   Updated: 2024/01/16 01:45:42 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_pwd(t_main *main)
{
	char	*str;

	str = NULL;
	if (main->pwd != NULL)
		free(main->pwd);
	main->pwd = getcwd(str, 0);
	printf("%s\n", main->pwd);
}

void	ft_env(t_main *main)
{
	main->env_list = main->env_head;
	if (main->lexer_list->next && main->lexer_list->next->type == ARGUMENT)
		printf("env: %s: No such file or directory\n", \
		main->lexer_list->next->content);
	else
	{
		while (main->env_list)
		{
			printf("%s\n", main->env_list->content);
			main->env_list = main->env_list->next;
		}
		main->env_list = main->env_head;
	}
}

void	ft_export(t_main	*main)
{
	main->i = 0;
	main->export_list = main->export_head;
	if (main->lexer_list->next == NULL || \
	main->lexer_list->next->type != ARGUMENT)
	{
		while (main->export_list)
		{
			main->i++;
			main->export_list = main->export_list->next;
		}
		main->export_list = main->export_head;
		print_export(main);
	}
	else
		add_export_env(main);
}

void	print_export(t_main	*main)
{
	main->flag = 0;
	while (0 < --main->i)
	{
		while (main->export_list->next)
		{
			if (main->export_list->content[0] > \
			main->export_list->next->content[0])
			{
				main->export_tmp = main->export_list->next->content;
				main->export_list->next->content = main->export_list->content;
				main->export_list->content = main->export_tmp;
			}
			main->export_list = main->export_list->next;
		}
		main->export_list = main->export_head;
	}
	main->i = 0;
	while (main->export_list)
		declare_export(main);
}
