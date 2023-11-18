/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:51:35 by yokten            #+#    #+#             */
/*   Updated: 2023/01/03 09:16:36 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	total_string(char	const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s == '\0')
			return (i);
		while (*s != c && *s)
			s++;
		i++;
	}
	return (i);
}

static int	total_char(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s != c && *s)
	{
		s++;
		i++;
	}
	return (i);
}

char	**ft_split(char	const	*s, char c)
{
	int		x;
	int		j;
	int		i;
	char	**a;

	if (!s)
		return (NULL);
	x = 0;
	j = total_string(s, c);
	a = ft_calloc(j + 1, sizeof(char *));
	if (!a)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			break ;
		i = total_char(s, c);
		a[x++] = ft_substr(s, 0, i);
		while (*s != c && *s)
			s++;
	}
	a[x] = NULL;
	return (a);
}
