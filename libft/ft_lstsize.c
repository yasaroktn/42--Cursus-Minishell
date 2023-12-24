/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:19:26 by yokten            #+#    #+#             */
/*   Updated: 2023/12/24 03:19:27 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	lst_len;

	lst_len = 1;
	if (!lst)
		return (0);
	while (lst -> next != NULL)
	{
		lst_len++;
		lst = lst -> next;
	}
	return (lst_len);
}
