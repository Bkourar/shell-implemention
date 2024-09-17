#include "minishell.h"

m_sh	*pi_processing_pro(char *str, m_sh **node, t_env **env)
{
	char		**cmd;
	m_sh		*new;
	int			i;

	new = (m_sh *) malloc(sizeof(m_sh));
	if (!new)
		return (NULL);
	cmd = pi_processing_expand(str, env, false);
	if (!cmd || !(*cmd))
		return (NULL);
	i = 0;
	new->args = (char **)malloc(sizeof(char *) * (count_wd(cmd) + 1));
	if (!new->args)
		return (NULL);
	while (cmd[i])
	{
		new = creat_commandline(&new, cmd[i], &i);
		i++;
	}
	new->args[i] = 0;
	return (new->dir = (*node)->dir, new->next = NULL, new);
}

t_sh	*pi_processing_cmd(t_sh **lst, char *str)
{
	t_sh	*tmp;
	char	c1;
	char	c2;

	tmp = (*lst);
	while (tmp != NULL)
	{
		c1 = tmp->token[0];
		c2 = tmp->token[1];
		if (tmp->type == err)
			pi_processing_err_3(lst, &tmp, c1, c2, str);
		tmp = tmp->nx;
	}
	tmp = ft_lstlast(lst);
	if (tmp->type == L_err && !check_herepipe(lst))
		return (run_heredoc(str, 0, lst, NULL), synatx_error(tmp->token), NULL);
	else if (tmp->type == L_err && check_herepipe(lst) != 0)
		return (synatx_error(tmp->token), NULL);
	if (pi_processing_err_1(lst, &tmp, str) || pi_processing_err_2(lst, str))
		return (NULL);
	else if (pi_processing_err_4(lst, 0, str) || pi_processing_err_5(lst, str))
		return (NULL);
	return (tmp);
}

char	*pi_process_expend(char *str, t_env **env)
{
	char	*cpy;
	int		i;
	int		j;

	cpy = (char *)ft_calloc(_ft_strlen(str) * 2, sizeof(char));
	if (!cpy)
		return (write(2, "allocation fail\n", 17), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (check_expend(str[i], str[i + 1]))
			change_space(&cpy[j], &cpy[j + 1], &j, &i);
		else if (str[i] == '\'' && str[i + 1] == '$' && check_hash(str, &i) == 2)
			change_hastag(&cpy[j], &cpy[j + 1], &j, &i);
		else if (str[i] == '\"' && str[i + 1] == '$')
			change_dbq(&cpy[j], &cpy[j + 1], &j, &i);
		else
				cpy[j++] = str[i++];
	}
	return (removed(cpy, '\'', 1, env));
}

static void	remove_quote(char *str, int *j)
{
	while (str[*j] && isquote(str[*j]))
		*j += 1;
}

char	*expanding(char *str, t_env **env)
{
	char	stack[255];
	t_env	*tp;
	int		j;
	int		i;

	tp = (*env);
	j = 0;
	i = 0;
	remove_quote(str, &i);
	while (str[i] && str[i]!= ' ' && !isquote(str[i]))
	{
		if (str[i] != '$')
			stack[j++] = str[i];
		else if ((str[i] == '$' && j != 0) || isquote(str[i]))
			break ;
		i++;
	}
	stack[j] = '\0';
	while (tp)
	{
		if (!strcmp(tp->var, (char const *)stack))
			return (ft_strdup(tp->value));
		tp = tp->next;
	}
	return (check_sq(str)); 
}
