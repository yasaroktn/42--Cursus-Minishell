/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:11:52 by yokten            #+#    #+#             */
/*   Updated: 2023/12/24 03:11:53 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_manage3(t_main *main, char *string)
{
	main->lexer_list->content = ft_string_join \
	(main->lexer_list->content, ft_substr(&string[main->a], 0, 1));
}
