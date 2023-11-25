#include "minishell.h"

void childforpipe(t_core *core, int flag)
{
    core->lexer = core->lexer->next;
    if (flag == 1)
    {
        close(core->pipes[0]);
        dup2(core->pipes[1], 1);
        close(core->pipes[1]);
    }
    close(core->pipes[1]);
    if (flag == 3)
    {
        close(core->pipes[1]);
        dup2(core->pipes[0], 0);
        close(core->pipes[0]);
    }
    close(core->pipes[0]);
}