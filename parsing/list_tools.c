#include "minishell.h"

t_tk	*ft_lstnew(char *content)
{
	t_tk	*n_node;

	n_node = (t_tk *)malloc(sizeof(t_tk));
	if (!n_node)
		return (NULL);
	n_node->token = ft_strdup(content);
	n_node->nx = NULL;
	return (n_node);
}

void	ft_lstadd_back_tsh(t_tk **lst, t_tk *new)
{
	t_tk	*temp;

	if (!(*lst))
	{
		(*lst) = new;
		new->pv = NULL;
		return ;
	}
	temp = *lst;
	while (temp->nx)
		temp = temp->nx;
	temp->nx = new;
	new->pv = temp;
}

void	ft_lstadd_front(t_tk **lst, t_tk *new)
{
	if (!lst || !new)
		return ;
	new->nx = *lst;
	*lst = new;
}

t_tk	*ft_lstlast(t_tk **lst)
{
	t_tk	*tmp;

	if (!lst)
		return (NULL);
	tmp = *lst;
	while (tmp != NULL)
	{
		if (tmp->nx == NULL)
			break;
		tmp = tmp->nx;
	}
	return (tmp);
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