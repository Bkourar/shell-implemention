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

t_exp	*ifconfigration(t_exp **l, t_env **ev, bool b)
{
	t_exp	*head;
	char	**s;
	int		wx;

	head = NULL;
	while ((*l))
	{
		if ((*l)->set->tp == exp && (*l)->set->st == not_join)
		{
			s = parse_value(&(*l), ev);
			autortion(s, &head, own_exp(4, (*l)->set->sp, 0), b);
		}
		else if ((*l)->set->tp == exp && (*l)->set->st == join)
		{
			wx = own_exp(4, (*l)->set->sp, 1);
			ft_lstadd_back_texp(&head, upgrade_input(s_and_r(&(*l), ev), b, &wx));
		}
		else
		{
			wx = own_exp((*l)->set->tp, (*l)->set->sp, (*l)->set->st);
			ft_lstadd_back_texp(&head, upgrade_input((*l)->input, b, &wx));
		}
		(*l) = (*l)->next;
	}
	return (free_exp(l), (*l) = head, (*l));
}

void	concatition(t_exp **lst, bool l)
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
			ft_lstadd_back_texp(&head, config(str, l)), free(str);
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
	int		i;

	head = NULL;
	head = update_input(str, &head);
	update_list(update_array(&head), &head);
	head = ifconfigration(&head, env, b);
	concatition(&head, b);
	spl = (char **)malloc((ft_lstsiz_exp(head) + 1) * sizeof(char *));
	if (!spl)
		write(2, "faile allocation\n", 18), exit(1);
	i = 0;
	while (head)
	{
		if (!ft_strcmp(head->input, " "))
			head = head->next;
		else
		{
			spl[i++] = ft_strdup(head->input);
			head = head->next;
		}
	}
	return (spl[i] = 0, spl);
}




