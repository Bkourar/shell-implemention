#include "minishell.h"

void	owner_premt(int *chmod, int	tp, int	wd, int	st)
{
	*chmod = tp + wd + st;
}

void	ft_lstadd_back_dir(t_dir **lst, t_dir *new)
{
	t_dir	*temp;

	if (!(*lst))
	{
		(*lst) = new;
		new->prv = NULL; 
		return ;
	}
	else if (new == NULL)
		return ;
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prv = temp; 
}

int	ft_lstsiz_dir(t_dir *lst)
{
	int		i;
	t_dir	*node;

	node = lst;
	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}

char	*search_in_eva(t_dir *nd, t_env **ev)
{
	t_env	*tp;

	tp = (*ev);
	while (tp)
	{
		if (tp->value != NULL && tp->value[0] != '\0' && !ft_strcmp(nd->input, tp->var))
			return (ft_strdup(tp->value));
		tp = tp->next;
	}
	return (NULL);
}
