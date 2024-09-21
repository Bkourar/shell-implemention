#include "expand.h"

void	skip_wspace(char *str, int *j, t_exp **lst)
{
	int		i;
	char	*dst;
	int		chmod;

	dst = (char *)malloc(sizeof(char) * _ft_strlen(str) + 1);
	if (!dst)
		write(2, "faile allocation\n", 18), exit(1);
	i = 0;
	chmod = 0;
	while (str[*j])
	{
		if (white_sp(str[*j]))
		{
			dst[i++] = str[*j];
			*j += 1;
		}
		else
			break ;
	}
	(dst[i] = '\0', premission(&chmod, 0, 2, 0));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, false, &chmod)), free(dst));
}

int	ft_lstsiz_exp(t_exp *lst)
{
	int		i;
	t_exp	*node;

	node = lst;
	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}

int	check_space(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int		check_dolar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	valid_join(t_exp *nd)
{
	if (nd == NULL)
		return (0);
	if (nd->set->st == join)
		return (1);
	else if (ft_strcmp(nd->input, " ") != 0 && 
		(nd->prv != NULL && nd->prv->set->st == join))
			return ( 1);
	else if (ft_strcmp(nd->input, " ") != 0 && 
		(nd->next != NULL && nd->next->set->st == join))
			return (1);
	else if (ft_strcmp(nd->input, " ") != 0 && 
		(nd->prv != NULL && ft_strcmp(nd->prv->input, " ") != 0))
			return (1);
	else if (ft_strcmp(nd->input, " ") != 0 && 
		(nd->next != NULL && ft_strcmp(nd->next->input, " ") != 0))
			return (1);
	return (0);
}
