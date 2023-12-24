/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:19:36 by yokten            #+#    #+#             */
/*   Updated: 2023/12/24 03:19:37 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	i = -1;
	p = (unsigned char *)s;
	while (++i < n)
		if (p[i] == (unsigned char)c)
			return ((unsigned char *)p + i);
	return (NULL);
}
