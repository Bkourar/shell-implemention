#include "expand.h"

void	search_and_replace(t_exp **txp, t_env **env, int b)
{
	t_env	*tnv;

	if ((*txp) == NULL || ((*txp)->next == NULL && (*txp)->set->tp == not_exp))
		return ;
	tnv = (*env);
	while (tnv && (*txp))
	{
		if ((*txp)->set->tp == not_exp)
			break ;
		else if (!ft_strcmp(tnv->var, (*txp)->input))
		{
			free((*txp)->input), b = 1;
			(*txp)->input = ft_strdup(tnv->value);
			if (!(*txp)->input)
				write(2, "faile allocation\n", 18), exit(1);
			break;
		}
		tnv = tnv->next;
	}
	if (b == 0 && (*txp)->set->tp == exp)
	{
		free((*txp)->input);
		(*txp)->input = ft_strdup("\0");
	}
	search_and_replace(&(*txp)->next, env, 0);
}

t_exp	*ft_lstlast_exp(t_exp **lst)
{
	t_exp	*tmp;

	if (!lst)
		return (NULL);
	tmp = *lst;
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
			break;
		tmp = tmp->next;
	}
	return (tmp);
}

int	white_sp(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	else if (c == '\r' || c == '\f')
		return (1);
	return (0);
}

void	update_list(char **in, t_exp **lst)
{
	t_exp	*head;
	int		i;
	int		j;

	i = 0;
	head = NULL;
	while (in[i])
	{
		j = 0;
		if (in[i][0] == '$')
			expand(in[i], &j, &head);
		else if (in[i][0] == '\"')
			parssing_expand(in[i], &j, &head);
		else if (in[i][0] == '\'')
			cin_singl_q(in[i], &j, &head);
		else
			copy_general(in[i], &j, &head);
		i++;
	}
	(*lst) = head;
}

char	**update_array(t_exp **lst)
{
	int		i;
	char	**data;
	t_exp	*tmp;

	data = (char **)malloc(ft_lstsiz_exp((*lst)) * sizeof(char *) + 1);
	if (!data)
		write(2, "faile allocation\n", 18), exit(1);
	i = 0;
	tmp = (*lst);
	while (tmp)
	{
		if (!ft_strcmp(tmp->input, """") || !ft_strcmp(tmp->input, "''"))
			tmp = tmp->next;
		else
		{
			if (tmp->set->sp == skip)
				data[i++] = ft_strdup(" ");
			else
				data[i++] = ft_strdup(tmp->input);
			tmp = tmp->next;
		}
	}
	data[i] = 0;
	return (data);
}
