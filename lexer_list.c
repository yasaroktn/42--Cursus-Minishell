/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:33:30 by yokten            #+#    #+#             */
/*   Updated: 2023/11/26 18:07:07 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexer_listnew(char *content)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	lexer_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp -> next)
		tmp = tmp -> next;
	tmp ->next = new;
}
