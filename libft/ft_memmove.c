/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:19:54 by yokten            #+#    #+#             */
/*   Updated: 2023/12/24 03:19:55 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p;
	unsigned char	*s;

	s = (unsigned char *)src;
	p = (unsigned char *)dst;
	if (!s && !p)
		return (0);
	if (s < p)
		while (len--)
			p[len] = s[len];
	else
		ft_memcpy(p, s, len);
	return (dst);
}
