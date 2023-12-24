/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:21:12 by yokten            #+#    #+#             */
/*   Updated: 2023/12/24 03:21:13 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*to_return;
	size_t	i;

	if (!s)
		return (NULL);
	to_return = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!to_return)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		to_return[i] = f(i, s[i]);
		i++;
	}
	to_return[i] = '\0';
	return (to_return);
}
