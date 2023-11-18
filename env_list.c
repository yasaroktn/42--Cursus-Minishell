#include "minishell.h"

t_env	*env_listnew(char *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp -> next)
		tmp = tmp -> next;
	tmp ->next = new;
}

t_export	*export_listnew(char *content)
{
	t_export	*node;

	node = malloc(sizeof(t_export));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	export_lstadd_back(t_export **lst, t_export *new)
{
	t_export	*tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp -> next)
		tmp = tmp -> next;
	tmp ->next = new;
}

void	add_export (t_core	*core)
{
	core->export_head = core->export;
	core->i = 0;
	core->export->content = core->tmp[core->i++];
	while (core->tmp[core->i])
	{
		if (core->tmp[core->i + 1])
			export_lstadd_back(&core->export,
				export_listnew(ft_strdup(core->tmp[core->i])));
		if (core->export->next != NULL)
			core->export = core->export->next;
		core->i++;
	}
}