
#include "./minishell.h"

void	ft_pwd_management(t_core	*core)
{
	char	*str;

	str = NULL;
	core->pwd = getcwd(str, 0);
	printf("%s\n", core->pwd);
}

void	ft_chdir(t_core	*core)
{
	core->i = 0;
	core->pwd = ft_strjoin("\033[0;35m", getcwd(core->pwd, 0));

	if (core->lexer->next)
		core->lexer = core->lexer->next;
	if (core->lexer && core->lexer->type == 2)
		core->i = chdir(core->lexer->content);
	else if (!core->lexer->next)
		core->i = chdir("/Users/sisen"/*yokten*/);
	else if (core->lexer->next && core->lexer->next->type == 2)
		printf("cd: too many arguments\n");
	if (core->i < 0)
		printf("cd: no such file or directory: %s\n"
			, core->lexer->content);
	core->pwd = ft_strjoin("\033[0;35m", getcwd(core->pwd, 0));
	core->readline = ft_strjoin(core->pwd, " > monkeys 🙉🙊🙈 :\033[0;37m ");
}

void	print_export(t_core	*core)
{
	core->flag = 0;
	while (0 < --core->i)
	{
		while (core->export->next)
		{
			if (core->export->content[0] > core->export->next->content[0])
			{				
				core->e_tmp = core->export->next->content;
				core->export->next->content = core->export->content;
				core->export->content = core->e_tmp;
			}
			core->export = core->export->next; 
		}
		core->export = core->export_head;
	}
	core->i = 0;
	while(core->export)
	{
		printf("declare -x ");
		while (core->export->content[core->i])
		{
			printf("%c", core->export->content[core->i]);
			if (core->export->content[core->i] == '=')
			{
				core->flag = 1;
				printf("%c", 34);
			}
			core->i++;
			if (core->export->content[core->i] == '\0' && core->flag == 1)
			{
				printf("%c", 34);
				core->flag = 0;
			}
		}
		core->i = 0;
		core->export = core->export->next;
		printf("\n");
	}
}

void	ft_export_management(t_core	*core)
{
	core->i = 0;
	core->k = 0;
	core->export = core->export_head;
	if (core->lexer->next == NULL || core->lexer->next->type != 2)
	{
		while (core->export)
		{
			core->i++;
			core->export = core->export->next;
		}
		core->export = core->export_head;
		print_export(core);
	}
	else
		add_export_env(core);
}

void	add_export_env(t_core	*core)
{
	core->lexer = core->lexer->next;
	core->l = 0;
		export_lstadd_back(&core->export,
				export_listnew(ft_strdup(core->lexer->content)));
 	while (core->lexer->content[core->l])
	{
		if (core->lexer->content[core->l] == '=')
		{
			env_lstadd_back(&core->env,
				env_listnew(ft_strdup(core->lexer->content)));
			break;
		}
		core->l++;
	}
	if (core->lexer->next != NULL && core->lexer->next->type == 2)
		add_export_env(core);
}
