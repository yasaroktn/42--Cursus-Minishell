#include "minishell.h"

void ft_redirections(t_core *core)
{
	core->l = 0;
	if ((!ft_strncmp(core->lexer->content, ">>", 2)))
	{
		create_file(core,1);
	}
	else if (!ft_strncmp(core->lexer->content, ">", 1))
	{
		create_file(core,2);
	}
	else if ((!ft_strncmp(core->lexer->content, "<<", 2)))
	{
		//input(core);
	}
	else if (!ft_strncmp(core->lexer->content, "<", 1))
	{
		input(core);
	}
}

void create_file(t_core *core,int mode)
{
	int		fd;
	fd = 0;
	if (mode == 2)
		fd = open(core->lexer->next->content, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (mode == 1)
		fd = open(core->lexer->next->content, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("minishell");
	}
	dup2(fd, 1);
	close(fd);
}

/*
void delete_file(t_core *core)
{

}*/

void input(t_core *core)
{
	int	fd;

	fd = open(core->lexer->next->content, O_RDONLY);
	if (fd == -1)
		return ;
	else
	{
		dup2(fd, 0);
		close(fd);
	}
	if (fd != -1)
		close(fd);
}
