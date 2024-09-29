#include "minishell.h"

void	free_exp(t_exp **lst)
{
	t_exp	*tmp;
	if (!lst || !(*lst))
		return ;
	tmp = (*lst)->next;
	while (tmp)
	{
		free((*lst)->input);
		free((*lst));
		(*lst) = tmp;
		tmp = tmp->next;
	}
	free((*lst)->input);
	free((*lst));
	free(lst);
	(*lst) = NULL;
}

void	free_dir(t_dir **lst)
{
	t_dir	*tmp;
	if (!lst || !(*lst))
		return ;
	tmp = (*lst)->next;
	while (tmp)
	{
		free((*lst)->input);
		free((*lst));
		(*lst) = tmp;
		tmp = tmp->next;
	}
	free((*lst)->input);
	free((*lst));
	free(lst);
	(*lst) = NULL;
}

void	parse_expand_dir(char *src, int *i, t_dir **head)
{
	if (src[*i] && src[*i] == '\"')
		*i += 1;
	while (src[*i] && src[*i] != '\"')
	{
		if (src[*i] == '$' && is_numeric(src[(*i + 1)]))
			i += 2;
		else if (valid_condtion(src, *i))
			expand_wqoute(src, i, head);
		else if (src[*i] == '\'')
			parsse_wesq(src, i, head);
		else
			copy_std_norm(src, i, head);
	}
	if (src[*i] && src[*i] == '\"')
		i += 1;
}

void	free_arr(char **arg)
{
	int	i;

	if (!arg)
		return ;
	if (!(*arg))
	{
		free(arg);
		return ;
	}
	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

int	own_exp(int tp, int sp, int st)
{
	int	chmod;

	chmod = tp + sp + st;
	return (chmod);
}