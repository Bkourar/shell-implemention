#include "minishell.h"

int	check_pipe(char *str, int j, int i)
{
	int		counter;
	char	c;

	counter = 0;
	while (str[i])
	{
		if (isquote(str[i]) && counter == 0)
		{
			c = str[i];
			counter++, i++;
			while (str[i] && str[i] != c)
			{
				if (i == j)
					return (1);
				i++;
			}
			if (str[i] && str[i] == c)
				counter++;
		}
		if (counter == 2)
			counter = 0;
		i++;
	}
	return (0);
}

int	check_heredoc(t_tk **lst)
{
	t_tk	*tp;
	int		i;

	i = 0;
	tp = (*lst);
	while (tp != NULL)
	{
		if (tp->type == heredoc)
			i++;
		tp = tp->nx;
	}
	return (i);
}

int	check_herepipe(t_tk **l)
{
	int		b1;
	int		b2;
	int		b3;

	b1 = 0;
	b2 = 0;
	b3 = 0;
	while ((*l) != NULL)
	{
		if ((*l)->type == heredoc && ((*l)->nx != NULL))
			b1 = 1;
		else if ((*l)->nx != NULL && (*l)->type == Pipe 
			&& (*l)->nx->type == Pipe)
			b2 = 1;
		else if (check_op1((*l)->type) && check_op1((*l)->type))
			b3 = 1;
		if(b1 == 1)
			return (0);
		else if(b2 == 1)
			return (1);
		else if(b3 == 1)
			return (2);
		(*l) = (*l)->nx;
	}
	return (3);
}

int	check_pos_here(t_tk **lst, t_tk **breaking)
{
	t_tk	*l;
	int		i;

	l = (*lst);
	i = 0;
	while (l != NULL)
	{
		if (l->type == heredoc && (l->nx != NULL && l->nx->type == word))
			i++;
		if (l == *breaking)
			return (i);
		l = l->nx;
	}
	return (0);
}

int	checker_typing(char const *santax)
{
	if (!ft_strcmp("<>", santax) || !ft_strcmp("><", santax) || !ft_strcmp("||", santax))
		return (1);
	else if (!ft_strcmp(">|", santax) || !ft_strcmp("<|", santax))
		return (1);
	else if (!ft_strcmp("|>", santax) || !ft_strcmp("|<", santax))
		return (2);
	return (0);
}