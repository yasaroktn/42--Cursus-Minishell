/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 03:00:09 by yokten            #+#    #+#             */
/*   Updated: 2023/01/03 09:15:52 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	int		s1_len;
	int		s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	a = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!a)
		return (NULL);
	ft_memcpy(a, s1, s1_len);
	ft_memcpy(a + s1_len, s2, s2_len);
	a[s1_len + s2_len] = '\0';
	return (a);
}
