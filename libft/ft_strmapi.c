/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 06:40:45 by yokten            #+#    #+#             */
/*   Updated: 2023/01/02 20:04:46 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*a;
	int		i;

	if (!s || !f)
		return (0);
	i = 0;
	a = (char *)malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (!a)
		return (0);
	while (s[i])
	{
		a[i] = f(i, s[i]);
		i ++ ;
	}
	a[i] = '\0';
	return (a);
}
