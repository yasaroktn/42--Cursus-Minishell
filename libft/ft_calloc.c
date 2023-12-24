/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:17:43 by yokten            #+#    #+#             */
/*   Updated: 2023/12/24 03:17:44 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*space;

	if (count == SIZE_MAX && size == SIZE_MAX)
		return (0);
	space = malloc(count * size);
	if (!space)
		return (0);
	ft_memset(space, 0, count * size);
	return (space);
}
