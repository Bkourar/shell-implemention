#include "minishell.h"

// void	free_linked(t_sh **likend)
// {
// 	t_sh	*elem;
// 	t_sh	*tmp;

// 	if (likend == NULL)
// 		return ;
// 	if (*likend == NULL)
// 	{
//         free((*likend)->token);
// 		free(*likend);
// 		return ;
// 	}
// 	elem = *likend;
// 	while (elem->next != NULL)
// 	{
// 		tmp = elem->next;
//         free(elem->token);
// 		free(elem);
// 		elem = tmp;
// 	}
// 	free(elem);
// }

int check_op(char c)
{
	if (!(c == '<' || c == '>' || c == '$' || c == '|' || c == '\"' || c == '\''))
		return (1);
	return (0);
}

int check_op1(ee i)
{
	if (i == input || i == output || i == append || i == heredoc)
		return (1);
	return (0);
}

int	check_heredoc(t_sh **lst)
{
	t_sh	*tp;
	int		i;

	i = 0;
	tp = (*lst);
	while (tp != NULL)
	{
		if (tp->type == heredoc)
			i++;
		tp = tp->next;
	}
	return (i);
}

int	check_herepipe(t_sh **l)
{
	int		b1;
	int		b2;
	int		b3;

	b1 = 0;
	b2 = 0;
	b3 = 0;
	while ((*l) != NULL)
	{
		if ((*l)->type == heredoc)
			b1 = 1;
		else if ((*l)->next != NULL && (*l)->type == Pipe 
			&& (*l)->next->type == Pipe)
			b2 = 1;
		else if (check_op1((*l)->type) && check_op1((*l)->type))
			b3 = 1;
		if(b1 == 1)
			return (0);
		else if(b2 == 1)
			return (1);
		else if(b3 == 1)
			return (2);
		(*l) = (*l)->next;
	}
	return (3);
}

int	check_pos_here(t_sh **lst, t_sh **breaking)
{
	t_sh	*l;
	int		i;

	l = (*lst);
	i = 0;
	while (l != NULL)
	{
		if (l->type == heredoc)
			i++;
		if (l == *breaking)
			return (i);
		l = l->next;
	}
	return (0);
}

