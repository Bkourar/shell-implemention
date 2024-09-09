#include "expand.h"

void	search_and_replace(t_exp **txp, t_env **env, int b)
{
	t_env	*tnv;

	if ((*txp) == NULL || ((*txp)->next == NULL && (*txp)->type == not_exp))
		return ;
	tnv = (*env);
	while (tnv && (*txp))
	{
		if ((*txp)->type == not_exp)
			break ;
		else if (!ft_strcmp(tnv->var, (*txp)->input))
		{
			free((*txp)->input), b = 1;
			(*txp)->input = ft_strdup(tnv->value);
			if (!(*txp)->input)
				write(2, "faile allocation\n", 18), exit(1);
			break;
		}
		tnv = tnv->next;
	}
	if (b == 0 && (*txp)->type == exp && ft_strcmp((*txp)->input, "?"))
	{
		free((*txp)->input);
		(*txp)->input = ft_strdup("\0");
	}
	search_and_replace(&(*txp)->next, env, 0);
}

// char	**parssing_expand(t_exp **head)
// {
// 	char	**data = NULL;
// 	// char	**spl;
// 	char	*str;
// 	t_exp	*tp;

// 	data = (char **)malloc(sizeof(char *) * ft_lstsize((*head)));
// 	str = ft_strdup((*head)->input);
// 	tp = (*head)->next;
// 	while (tp)
// 	{
// 		if (tp->state == join)
// 			str = ft_strjoin(str, tp->input);
// 		else
			
// 	}
// 	return (data);
// }
