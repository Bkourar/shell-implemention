#include "../prs/minishell.h"

void	ft_show_env(t_env *env)
{
	t_env	*e;

	e = env;
	while(e)
	{
		if (e->value)
			printf("%s=%s\n", e->var, e->value);
		e = e->next;
	}
}