#include "minishell.h"

t_redir	*get_token(char *inf, t_redir **l, t_env **env)
{
	char	*stock;
	int		i;
	int		j;

	i = 0;
	j = 0;
	(*l) = (t_redir *)malloc(sizeof(t_redir));
	if (!(*l))
		write(2, "allocation fail", 16), exit(1);
	if (inf[j] == '>' && inf[j + 1] == '>')
		(*l)->tp = app;
	else if (inf[j] == '<' && inf[j + 1] == '<')
		(*l)->tp = her_doc;
	else if (inf[j] == '<' && !check_dir(inf[j + 1]))
		(*l)->tp = in;
	else if (inf[j] == '>' && !check_dir(inf[j + 1]))
		(*l)->tp = out;
	else
		return (free(*l), NULL);
	while (inf[j] && (white_sp(inf[j]) || check_dir(inf[j])))
		j++;
	stock = pi_processing_redirect(&inf[j], env, (*l));
	if (stock == NULL)
		return (put_ambeg(&inf[j]), creat_node(NULL, (*l), env));
	return (creat_node(stock, (*l), env));
}

t_redir	 *get_token_dir(char *str, t_redir **lin, t_env **env, int i)
{
	t_redir	*new;

	new = NULL;
	while (str[i])
	{
		new = get_token(&str[i], &new, env);
		if (!new)
			i++;
		else
		{
			ft_lstadd_redir(lin, new);
			if (new->tp == out || new->tp == in )
				i++;
			else if (new->tp == her_doc || new->tp == app)
				i += 2;
			if (new->file_name != NULL)
				i += ft_strlen(new->file_name);
			else
				i += 2;
		}
	}
	return (*lin);
}

char	*pi_processing_dir(char *str, t_sh **h_n, t_env **env)
{
	t_redir	*head;
	char	stack[1000];
	int		i;
	int		j;

	head = NULL;
	head = get_token_dir(str, &head, env, 0);
	if (ambiguous_redirect(&head))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\''))
			i += replace_space(stack, &j, &str[i]);
		else if (i != 0 && str[i] == ' ' && check_dir(str[i - 1]))
			i += replace_space(stack, &j, &str[i]);
		else if (i != 0 && !check_dir(str[i]) && check_dir(str[i - 1]))
			i += replace_space(stack, &j, &str[i]);
		else if (check_dir(str[i]) || white_sp(str[i]))
			stack[j++] = ' ', i++;
		else
			stack[j++] = str[i++];
	}
	return ((*h_n)->dir = head, stack[j] = '\0', ft_strdup(stack));
}

static t_sh	*update_argement(char *cmd, t_sh **new_n, int i, t_env **env)
{
	char	stack[500];
	char	*k;
	char	*cpy;

	cpy = ft_strncpy(stack, cmd, i);
	(*new_n) = (t_sh *)malloc(sizeof(t_sh)); 
	if (!(*new_n))
		(write(2, "allocation fail", 16), exit(1));
	k  = pi_processing_dir(cpy, new_n, env);
	if (k == NULL)
		return (NULL);
	(*new_n) = pi_processing_pro(k, new_n, env);
	return (free(k), *new_n);
}

t_sh	*pi_processing_data(char *str, t_env **env , t_sh **head)
{
	t_sh	*new;
	int		i;

	i = -1;
	new = NULL;
	while (str[++i])
	{
		if (str[i] == '|' && !check_pipe(str, i, 0))
		{
			new = update_argement(str, &new, i, env);
			if (!new)
				return (NULL);
			ft_lstadd_back_msh(head, new);
			str = restory_cmd(str);
			i = -1;
		}
		else if (str[i] != '|' && str[i + 1] == '\0')
		{
			new = update_argement(str, &new, i + 1, env);
			if (!new)
				return (NULL);
			ft_lstadd_back_msh(head, new);
		}
	}
	return (*head);
}
