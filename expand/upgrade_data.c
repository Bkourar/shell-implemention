# include "minishell.h"

void	upgrade_setting(t_set **setting, int rwx)
{
	if (rwx == 4 || rwx == 6 || rwx == 5 || rwx == 7)
		(*setting)->tp = exp;
	else
		(*setting)->tp = not_exp;
	if (rwx == 2 || rwx == 6 || rwx == 3 || rwx == 7)
		(*setting)->sp = skip;
	else
		(*setting)->sp = not_skip;
	if (rwx == 1 || rwx == 5 || rwx == 3 || rwx == 7)
		(*setting)->st = join;
	else
		(*setting)->st = not_join;
}

t_exp	*upgrade_input(char *in, bool b, int *chmod)
{
	t_exp	*new;

	new = (t_exp *)malloc(sizeof(t_exp));
	if (!new)
		write(2, "faile allocation\n", 18), exit(1);
	new->set = (t_set *)malloc(sizeof(t_set));
	if (!new->set)
		write(2, "faile allocation\n", 18), exit(1);
	upgrade_setting(&new->set, *chmod);
	new->input = ft_strdup(in);
	new->logic = b;
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

void	premission(int *chmod, int tp, int sp, int st)
{
	*chmod = tp + sp + st;
}

char	*join_expand(t_exp **lst)
{
	char	*str;
	t_exp	*tp;

	tp = (*lst);
	str = NULL;
	while (tp)
	{
		str = ft_strjoin(str, tp->input);
		if (!str)
			write(2, "faile allocation\n", 18), exit(1);
		tp = tp->next;
	}
	return (str);
}

int	valid_condtion(char *str, int p)
{
	if (str[p] == '$' && valid_expand(str[p + 1]))
		return (1);
	return (0);
}
