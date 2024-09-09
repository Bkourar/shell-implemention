#include "minishell.h"

t_sh	*ft_lstnew(char *content)
{
	t_sh	*n_node;

	n_node = (t_sh *)malloc(sizeof(t_sh));
	if (!n_node)
		return (NULL);
	n_node->token = ft_strdup(content);
	n_node->nx = NULL;
	return (n_node);
}

void	ft_lstadd_back_tsh(t_sh **lst, t_sh *new)
{
	t_sh	*temp;

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

void	ft_lstadd_front(t_sh **lst, t_sh *new)
{
	if (!lst || !new)
		return ;
	new->nx = *lst;
	*lst = new;
}

t_sh	*ft_lstlast(t_sh **lst)
{
	t_sh	*tmp;

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

//modified !!!
int	ft_lstsize(m_sh *lst)
{
	int		i;
	m_sh	*node;

	node = lst;
	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}