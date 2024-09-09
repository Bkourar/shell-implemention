#include "../prs/minishell.h"

t_env	*env_lstnew(const char *var, const char *value)
{
	t_env *new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return NULL;

	new_node->var = ft_strdup(var);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;

	return (new_node);
}

void	env_lst_back(t_env **lst, t_env *new)
{
	t_env *temp;

	if (!(*lst))
	{
		*lst = new;
		return;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_del_one(t_env *head, const char *var)
{
	t_env	*temp;
	t_env	*prev;

	prev = NULL;
	temp = head;
	if (temp != NULL && ft_strncmp(temp->var, var, (ft_strlen(temp->var) + 1)) == 0)
	{
		head = temp->next;
		free(temp->var);
		free(temp->value);
		free(temp);
		return;
	}
	while (temp != NULL && ft_strncmp(temp->var, var, (ft_strlen(temp->var) + 1)) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL) return;
	prev->next = temp->next;
	free(temp->var);
	free(temp->value);
	free(temp);
}

void	ft_set_it(t_env *env, const char *var, const char *new_value)
{
	t_env	*temp;

	temp = env;
	while(temp)
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

	h = NULL;
	int i = 0;

	while (envir[i])
	{
		char *env = envir[i];
		char *eql = ft_strchr(env, '=');

		if (eql)
		{
			*eql = '\0';
			env_lst_back(&h, env_lstnew(env, eql + 1));
		}
		i++;
	}
	return (h);
}

static int	count_env_vars(t_env *env)
{
	t_env	*temp;
	int		count;

	temp = env;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

char	**env_to_arr(t_env *env)
{
	int		cnt;
	int		i;
	t_env	*temp;
	char	*joined_str;
	char	*temp_var;

	cnt = count_env_vars(env);
	char **arr = (char **)malloc((cnt + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	temp = env;
	i = 0;
	while (i < cnt)
	{
		temp_var = exec_join(ft_strdup(temp->var), "=");
		joined_str = exec_join(temp_var, temp->value);
		arr[i] = joined_str;
		temp = temp->next;
		i++;
	}
	arr[cnt] = NULL;
	return (arr);
}

char **environnement_pth(t_env *e)
{
	char	**arr;

	arr = NULL;
	while(e)
	{
		if (ft_strncmp(e->var, "PATH", 5) == 0)
		{
			arr = ft_split(e->value, ':');
		}
		e = e->next;
	}
	return (arr);
}

