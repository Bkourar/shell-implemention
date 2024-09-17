#include "expand.h"

int	valid_expand(char c)
{
	if (is_numeric(c) || c == '_' || is_alpha(c))
		return (1);
	return (0);
}

t_exp	*config(char *in, bool b)
{
	t_exp	*new;

	new = (t_exp *)malloc(sizeof(t_exp));
	if (!new)
		write(2, "faile allocation\n", 18), exit(1);
	new->set = (t_set *)malloc(sizeof(t_set));
	if (!new->set)
		write(2, "faile allocation\n", 18), exit(1);
	new->input = ft_strdup(in);
	new->logic = b;
	new->set->sp = 0;
	new->set->st = 0;
	new->set->tp = 0;
	new->next = NULL;
	return (new);
}

void	concanition(t_exp **lst, bool l)
{
	t_exp	*nd1;
	t_exp	*head;
	char	*str;

	nd1 = (*lst);
	head= NULL;
	str = NULL;
	while (nd1)
	{
		if (valid_join(nd1))
		{
			while (nd1 && valid_join(nd1))
			{
				str = ft_strjoin(str, nd1->input);
				nd1 = nd1->next;
			}
			ft_lstadd_back_texp(&head, config(str, l));
		}
		else
		{
			ft_lstadd_back_texp(&head, config(nd1->input, l));
			nd1 = nd1->next;
		}
	}
	(*lst) = head;
}

char	**pi_processing_expand(char *str, t_env **env, bool b)
{
	t_exp	*head;
	char	**spl;
	t_exp	*tp;
	int		i;


	head = NULL;
	if (b == false)
		head = update_input(str, &head);
	// else
	// 	head = update_redire(str, head);
	update_list(update_array(&head), &head);
	search_and_replace(&head, env, 0);
	concanition(&head, b);
	spl = (char **)malloc(ft_lstsiz_exp(head) * sizeof(char *) + 1);
	if (!spl)
		write(2, "faile allocation\n", 18), exit(1);
	tp = head;
	i = 0;
	while (tp)
	{
		if (!ft_strcmp(tp->input, " "))
			tp = tp->next;
		else
		{
			spl[i++] = ft_strdup(tp->input);
			tp = tp->next;
		}
	}
	spl[i] = 0;
	// spl = ft_split(join_expand(&head), ' ');
	return (spl);
}




