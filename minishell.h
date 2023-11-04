#ifndef     MINISHELL_H
# define    MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "structs.h"
#include  "libft/libft.h"


static void	lexer_lstadd_back(t_lexer **lst, t_lexer *new);
static t_lexer	*lexer_lstlast(t_lexer *lst);
static t_lexer	*lexer_listnew(char *content);

#endif