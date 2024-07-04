
#include "minishell.h"

t_sh	*ft_shell_last(t_sh **lst)
{
	t_sh	*tmp;

	if (!lst)
		return (NULL);
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_add_back(t_sh **lst, t_sh *new)
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

t_word *pars_word(t_word *node, char const *str)
{
	t_word *h;
	int	i;
	int	j;
	int	len;
	char *tmp;

	i = 0;
	h = NULL;
	while(str[i])
	{
		j = 0;
		len = 0;
		while(str[i + len] != '|' && str[i + len])
			len++;
		tmp = malloc(len + 1);
		while(str[i] != '|' && str[i])
			tmp[j++] = str[i++];
		tmp[j] = '\0';
		ft_lstadd_back(&h, ft_lstnew(tmp));
		if(str[i] == '|')
			(ft_lstadd_back(&h, ft_lstnew("|")), i++);
	}
	return (h);
}
