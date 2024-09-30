#include "minishell.h"

static void	upgrade_parameter(t_par **setting, int rwx)
{
	if (rwx == 4 || rwx == 6 || rwx == 5 || rwx == 7)
		(*setting)->tp = exp;
	else
		(*setting)->tp = not_exp;
	if (rwx == 2 || rwx == 6 || rwx == 3 || rwx == 7)
		(*setting)->wd = wrd;
	else
		(*setting)->wd = not_wrd;
	if (rwx == 1 || rwx == 5 || rwx == 3 || rwx == 7)
		(*setting)->st = join;
	else
		(*setting)->st = not_join;
}

t_dir	*upgrade_redirect(char *in, int *chmod, int j)
{
	t_dir	*new;

	new = (t_dir *)malloc(sizeof(t_dir));
	if (!new)
		write(2, "faile allocation\n", 18), exit(1);
	new->par = (t_par *)malloc(sizeof(t_par));
	if (!new->par)
		write(2, "faile allocation\n", 18), exit(1);
	upgrade_parameter(&new->par, *chmod);
	new->input = ft_strdup(in);
	if (!new->input)
		(write(2, "faile allocation\n", 18), exit(1));
	new->ambg = j;
	new->next = NULL;
	return (new);
}

static char	*concatition_dir(t_dir **lst)
{
	t_dir	*nd1;
	char	*str;

	str = NULL;
	if ((*lst) == NULL)
		return (str);
	nd1 = (*lst);
	while (nd1)
	{
		str = ft_strjoin(str, nd1->input);
		if (!str)
			(write(2, "faile allocation\n", 18), exit(1));
		nd1 = nd1->next;
	}
	return (str);
}

int	check_empty(char *s)
{
	if (s == NULL)
		return (0);
	if (s[2] == '\0' && s[0] == '\"' && s[1] == '\"')
		return (1);
	else if (s[2] == '\0' && s[0] == '\'' && s[1] == '\'')
		return (1);
	return (0);
}

char	*pi_processing_redirect(char *in, t_env **env, t_redir *d)
{
	t_dir	*head;
	char	**spl;
	char	*correct;

	head = NULL;
	if (d->tp == her_doc)
		return (in);
	if (check_empty(in))
		return (ft_strdup("\0"));
	head = analyse_input(in, &head);
	spl = mise_ajour_input(&head);
	if (!spl)
		(write(2, "faile allocation\n", 18), exit(1));
	upgrade_list(spl, &head);
	head = analyse_case_ambg(head, env);
	head = check_ambiguous_redirect(&head);
	correct = concatition_dir(&head);
	return (correct);
}
