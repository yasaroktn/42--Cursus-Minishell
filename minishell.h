#ifndef     MINISHELL_H
# define    MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "structs.h"


static void	lexer_lstadd_back(t_lexer **lst, t_lexer *new);

#endif