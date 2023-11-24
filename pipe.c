#include    "minishell.h"

void    childforpipe(t_core *core, int flag)
{
    if (flag == 1)
    {
        close (core->pipes[core->z][0]);
        dup2(core->pipes[core->z][1], 1);
        close (core->pipes[core->z][1]);
    }
    else if (flag == 3)
    {
            close(core->pipes[core->z][1]);
            dup2(core->pipes[core->z][0], 0);
            close(core->pipes[core->z][0]);
    }
     else if (flag == 2)
    {
        close(core->pipes[core->z - 1][1]);
        dup2(core->pipes[core->z - 1][0], 0);
        close(core->pipes[core->z - 1][0]);
        close(core->pipes[core->z][0]);
        dup2(core->pipes[core->z][1], 1);
        close(core->pipes[core->z][1]);
    }
}
