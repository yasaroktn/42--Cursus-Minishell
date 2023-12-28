/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:10:54 by yokten            #+#    #+#             */
/*   Updated: 2023/12/28 07:50:24 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_exp	*export_listnew(char *content)
{
	t_exp	*node;

	node = malloc(sizeof(t_exp));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	export_lstadd_back(t_exp **lst, t_exp *new)
{
	t_exp	*tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp -> next)
		tmp = tmp -> next;
	tmp ->next = new;
}

void	add_export(t_main	*main)
{
	main->export_head = main->export_list;
	main->c = 0;
	main->export_list->content = main->temp_env[main->c++];
	while (main->temp_env[main->c])
	{
		if (&main->temp_env[main->c + 1])
			export_lstadd_back(&main->export_list,
				export_listnew(ft_strdup(main->temp_env[main->c])));
		if (main->export_list->next != NULL)
			main->export_list = main->export_list->next;
		main->c++;
	}
}

void	add_env(t_main	*main)
{
	main->env_head = main->env_list;
	main->c = 0;
	main->env_list->content = main->temp_env[main->c++];
	while (main->temp_env[main->c])
	{
		if (&main->temp_env[main->c + 1])
			env_lstadd_back(&main->env_list,
				env_listnew(ft_strdup(main->temp_env[main->c])));
		if (main->env_list->next != NULL)
			main->env_list = main->env_list->next;
		main->c++;
	}
	main->env_list = main->env_head;
}
