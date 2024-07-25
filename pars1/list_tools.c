#include "minishell.h"

t_sh	*ft_lstnew(char *content)
{
	t_sh	*n_node;

	n_node = (t_sh *)malloc(sizeof(t_sh));
	if (!n_node)
		return (NULL);
	n_node->token = strdup(content);
	n_node->next = NULL;
	return (n_node);
}

void	ft_lstadd_back(t_sh **lst, t_sh *new)
{
	t_sh	*temp;

	if (!(*lst))
	{
		*lst = new;
		new->prev = NULL;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
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
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
			break;
		tmp = tmp->next;
	}
	return (tmp);
}
