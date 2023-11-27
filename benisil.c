 void	pre_exec(t_argv *trgt, t_info info)
{

}

int	exec_all(t_argv *exec, int max_proc)
{
	int		pid;
	int		fd;
	int		i;
	int		io[2];
	t_argv	*trgt;

	i = 0;
	fd = 0;
	while (i < max_proc)
	{
		trgt = get_trgt(exec);
		pipe(io);
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
			{
				dup2(fd, 0);
				close(fd);
			}
			if (i != max_proc - 1)
				dup2(io[1], 1);
			close(io[0]);
			close(io[1]);
			exit(exec_this(trgt));		
		}
		argv_destroy(trgt, (void (*)(void *))free);
		if (i != 0)
			close(fd);
		close(io[1]);
		fd = io[0];
		if (i == max_proc - 1)
			close(fd);
		++i;
	}
	return (wait_all(pid, max_proc));
}

/* void	ft_exec(t_core	*core)
{
	int i = 0;
	pid_t pid;
	while (i < core->child + 1)
	{
		int io[2];
		ft_access(core);
		int	fd = 0;
		pipe(io);
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
			{
				dup2(fd, 0);
				close(fd);
			}
			if (i != core->child)
				dup2(io[1], 1);
			close(io[0]);
			close(io[1]);
			execve(core->res[core->j], core->arg, core->env2);
		}
		if (i != 0)
				close(fd);
		close(io[1]);
		fd = io[0];
		if (i == core->child)
			close(fd);
		i++;
	}
	for (int i = 0; i < 2; i++)
		waitpid(pid, NULL, 0);
} */