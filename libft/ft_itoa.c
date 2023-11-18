/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 23:01:26 by yokten            #+#    #+#             */
/*   Updated: 2022/12/29 20:13:58 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_size(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
	{
		len++;
	}
	else if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10 ;
		len ++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*a;
	size_t	i;
	size_t	len;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = len_size(n);
	a = malloc((len + 1) * sizeof(char));
	if (!a)
		return (0);
	if (n < 0)
	{
		a[0] = 45;
		n *= -1;
		i++;
	}
	a[len] = '\0';
	while (i < len--)
	{
		a[len] = (n % 10) + '0';
		n /= 10;
	}
	return (a);
}
