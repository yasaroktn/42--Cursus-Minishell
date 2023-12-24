/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:20:56 by yokten            #+#    #+#             */
/*   Updated: 2023/12/24 03:20:57 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!dst && !size)
		return (0);
	dst_len = ft_strlen(dst);
	if (dst_len >= size)
		return (src_len + size);
	ft_strlcpy((dst + dst_len), src, size - dst_len);
	return (dst_len + src_len);
}
