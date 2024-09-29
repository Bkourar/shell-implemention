#include "minishell.h"

void	ft_del_one(t_env *head, const char *var);
void	ft_set_it(t_env *env, const char *var, const char *new_value);
void	ft_set_it(t_env *env, const char *var, const char *new_value);
t_env	*parse_env(char **envir);
void	ft_show_env(t_env *env);

void	ft_del_one(t_env *head, const char *var)
{
	t_env	*t;
	t_env	*prev;

	prev = NULL;
	t = head;
	if (t != NULL && ft_strncmp(t->var, var, (ft_strlen(t->var) + 1)) == 0)
	{
		head = t->next;
		free(t->var);
		free(t->value);
		free(t);
		return ;
	}
	while (t != NULL && ft_strncmp(t->var, var, (ft_strlen(t->var) + 1)) != 0)
	{
		prev = t;
		t = t->next;
	}
	if (t == NULL)
		return ;
	prev->next = t->next;
	free(t->var);
	free(t->value);
	free(t);
}

void	ft_set_it(t_env *env, const char *var, const char *new_value)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(var, temp->var, ft_strlen(var)) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(new_value);
		}
		temp = temp->next;
	}
}

t_env	*parse_env(char **envir)
{
	t_env	*h;
	char	*env;
	char	*eql;
	int		i;

	h = NULL;
	i = 0;
	while (envir[i])
	{
		env = envir[i];
		eql = ft_strchr(env, '=');
		if (eql)
		{
			*eql = '\0';
			env_lst_back(&h, env_lstnew(env, eql + 1));
		}
		i++;
	}
	return (h);
}

void	ft_show_env(t_env *env)
{
	t_env	*e;

	e = env;
	while (e)
	{
		if (e->value)
			ft_putstr_x(e->var, e->value, NULL, 1);
		e = e->next;
	}
}
