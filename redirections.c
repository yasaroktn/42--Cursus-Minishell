#include "minishell.h"

void ft_redirections(t_core *core)
{
	core->l = 0;
	printf("sorun ne\n");
	if ((!ft_strncmp(core->lexer->content, ">>", 2)))
	{
		printf("basardım\n");
	}
	else if (!ft_strncmp(core->lexer->content, ">", 1))
	{
		printf(">> is working\n");
		printf("%s\n", core->lexer->next->content);
	}
}

void create_file(t_core *core)
{
	
}

/*void delete_file(t_core *core)
{

}*/