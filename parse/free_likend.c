#include "minishell.h"
#include "minishell1.h"

void	free_tsh(t_sh **likend)
{
	t_sh	*elem;
	t_sh	*tmp;

	if (likend == NULL)
		return ;
	if (*likend == NULL)
	{
		free((*likend)->token);
		free((*likend)->stat);
		free(*likend);
		return ;
	}
	elem = *likend;
	while (elem->nx != NULL)
	{
		tmp = elem->nx;
		free(elem->token);
		free(elem->stat);
		free(elem);
		elem = tmp;
	}
	free(elem);
}

void	free_msh(m_sh **likend)
{
	m_sh	*elem;
	m_sh	*tmp;

	if (likend == NULL)
		return ;
	if (*likend == NULL)
	{
		free((*likend)->args[0]);
		free((*likend)->args[1]);
		free((*likend)->dir->file_name);
		free((*likend)->dir);
		free((*likend));
		return ;
	}
	elem = *likend;
	while (elem->next != NULL)
	{
		tmp = elem->next;
		free(elem->dir->file_name);
		free(elem->args[0]);
		free(elem->args[1]);
		free(elem->dir), free(elem);
		elem = tmp;
	}
	free(elem);
}

// int check_op(char c)
// {
// 	if (!(c == '<' || c == '>' || c == '$' || c == '|' || c == '\"' || c == '\''))
// 		return (1);
// 	return (0);
// }

// int check_op1(ee i)
// {
// 	if (i == input || i == output || i == append || i == heredoc)
// 		return (1);
// 	return (0);
// }

// int	check_heredoc(t_sh **lst)
// {
// 	t_sh	*tp;
// 	int		i;

// 	i = 0;
// 	tp = (*lst);
// 	while (tp != NULL)
// 	{
// 		if (tp->type == heredoc)
// 			i++;
// 		tp = tp->nx;
// 	}
// 	return (i);
// }

// int	check_herepipe(t_sh **l)
// {
// 	int		b1;
// 	int		b2;
// 	int		b3;

// 	b1 = 0;
// 	b2 = 0;
// 	b3 = 0;
// 	while ((*l) != NULL)
// 	{
// 		if ((*l)->type == heredoc)
// 			b1 = 1;
// 		else if ((*l)->nx != NULL && (*l)->type == Pipe 
// 			&& (*l)->nx->type == Pipe)
// 			b2 = 1;
// 		else if (check_op1((*l)->type) && check_op1((*l)->type))
// 			b3 = 1;
// 		if(b1 == 1)
// 			return (0);
// 		else if(b2 == 1)
// 			return (1);
// 		else if(b3 == 1)
// 			return (2);
// 		(*l) = (*l)->nx;
// 	}
// 	return (3);
// }

// int	check_pos_here(t_sh **lst, t_sh **breaking)
// {
// 	t_sh	*l;
// 	int		i;

// 	l = (*lst);
// 	i = 0;
// 	while (l != NULL)
// 	{
// 		if (l->type == heredoc)
// 			i++;
// 		if (l == *breaking)
// 			return (i);
// 		l = l->nx;
// 	}
// 	return (0);
// }

