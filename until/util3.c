/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 05:47:04 by yokten            #+#    #+#             */
/*   Updated: 2023/12/28 15:46:51 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	copy_env(t_main *main)
{
	main->env_list = main->env_head;
	main->z = 0;
	while (main->env_list)
	{
		main->env_list = main->env_list->next;
		main->z++;
	}
	main->env2 = malloc(sizeof(char *) * main->z);
	main->env_list = main->env_head;
	main->z = 0;
	while (main->env_list)
	{
		main->env2[main->z++] = main->env_list->content;
		main->env_list = main->env_list->next;
	}
}

void	redir_control(t_main	*main)
{
	if (main->lexer_list->next->next && \
	main->lexer_list->next->next->type == REDIR)
	{
		dup2(main->heredoc_fd[0], 0);
		main->lexer_list = main->lexer_list->next->next;
		ft_redirections(main);
	}
	close (main->heredoc_fd[1]);
}
