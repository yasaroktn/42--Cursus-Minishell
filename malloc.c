#include "minishell.h"

void	init_core(t_core *core)
{
	core->child = 1;
	core->p = 0;
	core->i = 0;
	core->j = 0;
	core->k = 0;
	core->l = 0;
	core->t = 0;
	core->flag = 0;
	core->lex_flag = 0;
	core->err_code = 0;
	core->swap = NULL;
	core->expanded = NULL;
	core->pwd = ft_strjoin("\033[0;35m", getcwd(core->pwd, 0));
}
