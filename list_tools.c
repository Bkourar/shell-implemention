#include "minishell.h"

t_sh	*ft_lstnew(char *content)
{
	t_sh	*n_node;

	n_node = malloc(sizeof(t_sh));
	if (!n_node)
		return (NULL);
	n_node->value = content;
	n_node->next = NULL;
	return (n_node);
}

void	ft_lstadd_back(t_sh **lst, t_sh *new)
{
	t_sh	*temp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_lstadd_front(t_sh **lst, t_sh *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

int	ft_lstsize(t_sh *lst)
{
	int		i;
	t_sh	*node;

	node = lst;
	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}

t_sh	*ft_lstlast(t_sh **lst)
{
	t_sh	*tmp;

	if (!lst)
		return (NULL);
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
