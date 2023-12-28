/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:13:45 by yokten            #+#    #+#             */
/*   Updated: 2023/12/28 22:06:17 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	clean_shell(void)
{
	printf("\033[001;1H\033[2J");
}

int	history_check(t_main *main)
{
	while (main->input[main->i] == ' ')
		main->i++;
	if (main->input[main->i] == '\0')
		return (0);
	else
		return (1);
}

void	init_main(t_main *main)
{
	main->i = 0;
	main->j = 0;
	main->a = -1;
	main->pipe_count = 0;
	main->double_q = 0;
	main->single_q = 0;
	main->err_no = 0;
	main->b = 0;
	main->pid = malloc(sizeof(int) * 100);
	main->pwd = getcwd(NULL, 0);
	main->env_list = malloc(sizeof(t_env));
	main->export_list = malloc(sizeof(t_exp));
}

char	*ft_string_join(char const *s1, char const *s2)
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
	free((void *)s2);
	s1 = NULL;
	s2 = NULL;
	return (new_str);
}

char	*ft_substring(char const *s, unsigned int start, size_t len)
{
	char	*a;
	size_t	i;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	a = ft_calloc((len + 1), sizeof(char));
	if (!a)
		return (0);
	i = 0;
	while (s[start] && i < len)
	{
		a[i] = s[start];
		start++;
		i++;
	}
	a[i] = '\0';
	free((void *)s);
	return (a);
}
