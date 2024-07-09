#include "minishell.h"

void	free_linked(t_sh **likend)
{
	t_sh	*elem;
	t_sh	*tmp;

	if (likend == NULL)
		return ;
	if (*likend == NULL)
	{
        free((*likend)->token);
        free((*likend)->type);
		free(*likend);
		return ;
	}
	elem = *likend;
	while (elem->next != NULL)
	{
		tmp = elem->next;
        free(elem->token);
        free(elem->type);
		free(elem);
		elem = tmp;
	}
	free(elem);
}

int check_op(char c)
{
	if (!(c == '<' || c == '>' || c == '$' || c == '|' || c == '$' || c == '\"' || c == '\''))
		return (1);
	return (0);
}