/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:47:29 by yokten            #+#    #+#             */
/*   Updated: 2022/12/28 15:03:44 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*a;
	size_t			i;

	a = (unsigned char *)s;
	i = 0;
	if (!n)
		return (NULL);
	while (i < n)
	{
		if (a[i] == (unsigned char)c)
		{
			return ((void *)&s[i]);
		}
		i++;
	}
	if (c == '\0')
	{
		return ((void *)&s[i]);
	}
	return (NULL);
}
