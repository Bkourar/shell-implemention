#include "minishell.h"


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

	data = (char **)malloc((ft_lstsiz_exp((*lst)) + 1) * sizeof(char *));
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

char	*s_and_r(t_exp **txp, t_env **env)
{
	t_env	*tp;

	tp = (*env);
	while (tp)
	{
		if (!ft_strcmp((*txp)->input, tp->var))
			return (ft_strdup(tp->value));
		tp = tp->next;
	}
	if (tp == NULL && ft_strcmp((*txp)->input, "?"))
		return (ft_strdup("\0"));
	else if (tp == NULL && !ft_strcmp((*txp)->input, "?"))
		return (ft_strdup("affich stuts"));
	return (NULL);
}