/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:13:40 by yokten            #+#    #+#             */
/*   Updated: 2023/12/28 07:50:24 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*split_dolar_or_space(char *string, t_main *main)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(string) + 1));
	while (string[main->a])
	{
		if (string[main->a] == '$')
		{
			main->a++;
			while (ft_isalnum(string[main->a]) || string[main->a] == '_' )
			{
				tmp[j] = string[main->a];
				main->a++;
				j++;
			}
			tmp[j] = '\0';
			main->a--;
			return (tmp);
		}
		main->a++;
	}
	return (tmp);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
		{
			return (*((unsigned char *)s1) - *((unsigned char *)s2));
		}
		s1++;
		s2++;
	}
	return (0);
}

void	exit_shell(t_main	*main, int flag)
{
	printf("exit\n");
	if (flag == 0)
		exit(0);
	else if (flag == 2)
	{
		printf("too many arguments\n");
		main->err_no = 1;
	}
	else if (flag == 1)
	{
		printf("numeric argument required\n");
		exit(255);
	}
}

void	init_lists(char **env, t_main *main)
{
	while (env[main->b])
		main->b++;
	main->temp_env = malloc(sizeof(t_env) * main->b);
	main->b = 0;
	while (env[main->b])
	{
		main->temp_env[main->b] = ft_strdup(env[main->b]);
		main->b++;
	}
	main->temp_env[main->b] = NULL;
	add_export(main);
	add_env(main);
}

void	reset_main(t_main *main)
{
	main->process_iterator = 0;
	main->x = -1;
}
