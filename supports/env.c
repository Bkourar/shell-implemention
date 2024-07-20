#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_env
{
	char	*var;
	char	*value;
	struct s_env	*next;
}			t_env;


char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
	{
		return ((char *)(s + i));
	}
	return (0);
}

t_env *env_lstnew(const char *var, const char *value)
{
	t_env *new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return NULL;

	new_node->var = strdup(var);
	new_node->value = strdup(value);
	new_node->next = NULL;

	return new_node;
}


void env_lst_back(t_env **lst, t_env *new)
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

t_env *parse_envp(char *const envp[])
{
	t_env *h;

	h = NULL;
	int i = 0;

	while (envp[i])
	{
		char *env = envp[i];
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
void print_list(const t_env *h)
{
	while (h)
	{
		printf("%s=%s\n", h->var, h->value);
		h = h->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_env *env_list = parse_envp(envp);

	print_list(env_list);

	return 0;
}

