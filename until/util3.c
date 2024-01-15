/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 05:47:04 by yokten            #+#    #+#             */
/*   Updated: 2024/01/16 01:51:00 by yokten           ###   ########.fr       */
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

char	*ft_getenv(char	*str, t_main	*main)
{
	int		i;
	char	**tmp;

	main->env_list = main->env_head;
	i = 0;
	while (main->env_list)
	{
		tmp = ft_split(main->env_list->content, '=');
		if (!ft_strcmp(str, tmp[0]))
		{
			str = ft_strdup(tmp[1]);
			while (tmp[i])
				free(tmp[i++]);
			free(tmp);
			return (str);
		}
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
		i = 0;
		main->env_list = main->env_list->next;
	}
	return (NULL);
}

char	*ft_string_join2(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1)
		s1 = ft_strdup("");
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = ft_calloc((s1_len + s2_len + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, s1_len);
	ft_memcpy(new_str + s1_len, s2, s2_len);
	free((void *)s1);
	s1 = NULL;
	s2 = NULL;
	return (new_str);
}
