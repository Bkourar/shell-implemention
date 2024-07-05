#include "minishell.h"

t_word	*ft_lstnew(char *content)
{
	static int i;
	t_word	*n_node;

	n_node = malloc(sizeof(t_word));
	if (!n_node)
		return (NULL);
	n_node->token = content;
	if (!(strcmp("|", n_node->token)))
		n_node->type = strdup("pipe");
	else
		n_node->type = strdup("word");
	n_node->stat = strdup("genral");
	if (!n_node->stat || !n_node->type)
		return (NULL);
	n_node->next = NULL;
	if (i == 11)
	{
		puts("1234567");
		puts(n_node->token);
		puts(n_node->stat);
		puts(n_node->type);
	}
	i++;
	return (n_node);
}

void	ft_lstadd_back(t_word **lst, t_word *new)
{
	t_word	*temp;

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

void	ft_lstadd_front(t_word **lst, t_word *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

int	ft_lstsize(t_word *lst)
{
	int		i;
	t_word	*node;

	node = lst;
	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}

t_word	*ft_lstlast(t_word **lst)
{
	t_word	*tmp;

	if (!lst)
		return (NULL);
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
