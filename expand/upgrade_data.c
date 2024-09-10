# include "expand.h"


t_exp	*upgrade_input(char *in, bool b, t_type l, t_state st)
{
	t_exp	*new;

	if ((in[0] == ' ' && in[1] == '\0') || in[0] == '\0')
	{
		puts("pooom");
		return NULL;
	}
	new = (t_exp *)malloc(sizeof(t_exp));
	if (!new)
		write(2, "faile allocation\n", 18), exit(1);
	new->input = ft_strdup(in);
	new->logic = b;
	new->type = l;
	new->state = st;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_texp(t_exp **lst, t_exp *new)
{
	t_exp	*temp;

	if (!(*lst))
	{
		(*lst) = new;
		new->prv = NULL; 
		return ;
	}
	else if (new == NULL)
		return ;
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prv = temp; 
}

void	upgrade_type(t_type *tp, bool logic)
{
	if (logic == true)
		*tp = exp;
	else
		*tp = not_exp;
}

char	*join_expand(t_exp **lst)
{
	char	*str;
	t_exp	*tp;

	tp = (*lst);
	str = NULL;
	while (tp)
	{
		// printf("{%s}\n", tp->input);
		// if (tp->type == exp)
		// 	printf("exp\n");
		// else
		// 	printf("not_exp\n");
		str = ft_strjoin(str, tp->input);
		if (!str)
			write(2, "faile allocation\n", 18), exit(1);
		tp = tp->next;
	}
	return (str);
}

int	valid_condtion(char *str, int p)
{
	if (str[p] == '\"' && str[p + 1] == '$' && valid_expand(str[p + 2]))
		return (1);
	else if (str[p] == '$' && valid_expand(str[p + 1]))
	{
		if (p != 0 && str[p - 1] != '\'')
			return (1);
	}
	return (0);
}