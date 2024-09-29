#include "minishell.h"

int	check_error_ambiguous(t_dir *nd, t_dir **head)
{
	int	i;

	if (nd == NULL)
		return (puts("0"), 0);
	i = ft_lstsiz_dir((*head));
	if (nd->ambg == ambg_5)
		return (puts("5"), 1);
	else if (nd->ambg == ambg_1 && i == 1)
		return (puts("1"), 1);
	else if (nd->ambg == ambg_2 && (nd->prv != NULL && nd->prv->par->wd == wrd))
		return (puts("2"), 1);
	else if (nd->ambg == ambg_3 && (nd->next != NULL && nd->next->par->wd == wrd))
		return (puts("3"), 1);
	else if (nd->ambg == ambg_4 && i > 1)
		return (puts("4"), 1);
	return (puts("00"), 0);
}

int	sort_case_ambg(char *in)
{
	int	j;
	int	i;

	if (in == NULL)
		return (1);
	i = count_word(in, ' ');
	j = _ft_strlen(in);
	if (i > 1)
		return (5);
	else if (white_sp(in[0]) && white_sp(in[j - 1]))
		return (4);
	else if (white_sp(in[0]) && !white_sp(in[j - 1]))
		return (2);
	else if (white_sp(in[j - 1]) && !white_sp(in[0]))
		return (3);
	return (6);
}

t_dir	*analyse_case_ambg(t_dir *tp, t_env **ev)
{
	char	*in;
	t_dir	*lst;

	lst = NULL;
	while (tp)
	{
		if (tp->par->st == not_join && tp->par->tp == exp)
		{
			in = search_in_eva(tp, ev);
			(ft_lstadd_back_dir(&lst, config_redirect(in, sort_case_ambg(in), tp)), free(in));
		}
		else if (tp->par->st == join && tp->par->tp == exp)
		{
			in = search_in_eva(tp, ev);
			(ft_lstadd_back_dir(&lst, config_redirect(in, 0, tp)), free(in));
		}
		else
		{
			ft_lstadd_back_dir(&lst, config_redirect(tp->input, 0, tp));
		}
		tp = tp->next;
	}
	return (lst);
}

t_dir	*check_ambiguous_redirect(t_dir **l)
{
	t_dir	*tp;

	tp = (*l);
	while (tp)
	{
		if (tp->ambg == 0)
			tp = tp->next;
		else
		{
			if (check_error_ambiguous(tp, l) != 0)
				return (NULL);
			else
				tp = tp->next;
		}
	}
	return (tp = (*l), tp);
}

void	put_ambeg(char *str)
{
	write(2, "bash : ", 8);
	write(2, str, ft_strlen(str));
	write(2, ": ambiguous redirect\n", 22);
	ft_hrb(1, 1);
}