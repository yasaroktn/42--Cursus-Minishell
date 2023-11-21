#include "minishell.h"

//fix the seg of third
void	ft_unset_management(t_core *core)
{
	core->lexer = core->lexer->next;
	if (core->lexer->content)
		core->tmp_joined = ft_strjoin(core->lexer->content, "=");
	core->i = -1 ;
	while (core->tmp[++core->i])
	{
		if (!ft_strncmp(core->tmp_joined, core->tmp[core->i],
				ft_strlen(core->tmp_joined)))
		{
			while (core->tmp[core->i])
			{
				core->tmp[core->i] = core->tmp[core->i + 1];
				core->i++;
			}
			return ;
		}
	}
}

//make a core->integer 0er function, call it at the start of this func, check other funcs to see if it works as well
void	ft_builtins(t_core *core)
{
	if (core->lexer->type == 1)
	{
		if (!ft_strncmp(core->lexer->content, "echo", 4)
			&& ft_strlen(core->lexer->content) == 4)
			ft_echo_management(core);
		else if (!ft_strncmp(core->lexer->content, "unset", 5)
			&& ft_strlen(core->lexer->content) == 5)
			ft_unset_management(core);
		else if (!ft_strncmp(core->lexer->content, "exit", 4)
			&& ft_strlen(core->lexer->content) == 4)
			ft_exit_management(core);
		else if (!ft_strncmp(core->lexer->content, "pwd", 3)
			&& ft_strlen(core->lexer->content) == 3)
			ft_pwd_management(core);
  	 	else if (!ft_strncmp(core->lexer->content, "env", 3)
			&& ft_strlen(core->lexer->content) == 3)
			ft_env_management(core);
		else if (!ft_strncmp(core->lexer->content, "cd", 2)
			&& ft_strlen(core->lexer->content) == 2)
			ft_chdir(core);
		else if (!ft_strncmp(core->lexer->content, "export", 6)
			&& ft_strlen(core->lexer->content) == 6)
			ft_export_management(core);
		//printf("command not found: %s\n", core->lexer->content);
	}
}

int	echo_n_control(t_core *core)
{
	core->i = 1;
	while (core->lexer->content[core->i])
	{
		if (core->lexer->content[core->i] != 'n')
			return (0);
		core->i++;
	}
	return (1);
}

void	ft_echo_management(t_core *core)
{
	core->flag = 1;
	if (core->lexer->next != NULL)
	{	
		core->lexer = core->lexer->next;
		if (!ft_strncmp(core->lexer->content, "-n", 2) && echo_n_control(core))
			core->flag = 0;
		while (!ft_strncmp(core->lexer->content, "-n", 2) && echo_n_control(core))
			core->lexer = core->lexer->next;
		while (core->lexer)
		{
			if (core->lexer->type == 2)
				printf("%s ", core->lexer->content);
			else if (core->lexer->type == 3)
				ft_builtins(core);
			core->lexer = core->lexer->next;
		}
	}
	if(core->flag == 1)
		printf("\n");
}

int	exit_control(t_core *core)
{
	core->i = 0;
	while (ft_isdigit(core->lexer->content[core->i]))
		core->i++;
	while (core->lexer->content[core->i] == ' ')
		core->i++;
	if (core->lexer->content[core->i] == '\0')
		return (1);
	else
		return (0);
}

void	ft_exit_management(t_core *core)
{
	core->i = 0;
	if (core->lexer->next != NULL)
	{
		core->lexer = core->lexer->next;
		if (!exit_control(core))
		{
			core->err_code = 255;
			printf("exit : %s: numaric argument required\n",
				core->lexer->content);
			exit(0);
		}
		else if (core->lexer->next != NULL && core->lexer->type == 2)
		{
			printf("exit: too many arguments\n");
			core->err_code = 1;
		}
		else if (exit_control(core))
		{
			core->err_code = ft_atoi(core->lexer->content);
			if (core->err_code > 255)
				core->err_code = 255;
			printf("exit\n");
			exit(0);
		}
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}
