#include "minishell.h"

int	ambiguous_redirect(t_redir **hd)
{
	t_redir	*tp;

	tp = (*hd);
	while (tp)
	{
		if (tp->file_name == NULL && tp->fd_her == -1)
			return (1);
		tp = tp->next;
	}
	return (0);
}

t_dir	*config_redirect(char *in, int j, t_dir *nd)
{
	t_dir	*new;

	new = (t_dir *)malloc(sizeof(t_dir));
	if (!new)
		write(2, "faile allocation\n", 18), exit(1);
	new->par = (t_par *)malloc(sizeof(t_par));
	if (!new->par)
		write(2, "faile allocation\n", 18), exit(1);
	if (in == NULL)
		new->input = NULL;
	else
	{
		new->input = ft_strdup(in);
		if (!new->input)
			(write(2, "faile allocation\n", 18), exit(1));
	}
	new->par->st = nd->par->st;
	new->par->tp = nd->par->tp;
	new->par->wd = nd->par->wd;
	new->ambg = j;
	new->next = NULL;
	return (new);
}
