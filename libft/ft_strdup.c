/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:20:42 by yokten            #+#    #+#             */
/*   Updated: 2023/12/24 03:20:43 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*new_str;

	s_len = ft_strlen(s);
	new_str = malloc(s_len + 1 * sizeof(char));
	if (!new_str)
		return (0);
	ft_strcpy(new_str, s);
	return (new_str);
}
