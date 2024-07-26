#include "minishell.h"
// #include "minishell1.h"

t_sh	*ft_shell_last(t_sh **lst)
{
	t_sh	*tmp;

	if (!lst)
		return (NULL);
	tmp = *lst;
	while (tmp->nx)
		tmp = tmp->nx;
	return (tmp);
}

t_sh	*parse_commands_2(t_sh **n, char const *string)
{
	if (!strcmp("<", string))
		(*n)->type = input;
	else if (!strcmp(">", string))
		(*n)->type = output;
	else if (!strcmp("<<", string))
		(*n)->type = heredoc;
	else if (!strcmp(">>", string))
		(*n)->type = append;
	else if (!strcmp("<>", string) || !strcmp("><", string) || !strcmp("|>", string) 
		|| !strcmp("|<", string) || !strcmp(">|", string) || !strcmp("<|", string) 
		|| !strcmp("||", string))
		(*n)->type = err;
	else if (!strcmp("|", string))
		(*n)->type = Pipe;
	else if (!strcmp("\"", string) || !strcmp("'", string))
	{
		if (!strcmp("\"", string))
			(*n)->type = d_quot;
		else
			(*n)->type = s_quot;
		(free((*n)->stat), (*n)->stat = strdup("spicial"));
	}
	else if (!strcmp("$", string))
		(*n)->type = dolar;
	return (*n);
}

t_sh	*parse_commands_1(char const *st)
{
	t_sh	*new;

	new = NULL;
	if (!check_op(st[0]) && (st[1] == '\0' || st[2] == '\0'))
	{
		new = (t_sh *)malloc(sizeof(t_sh));
		if (!new)
			return(NULL);
		new->token = strdup(st);
		new->stat = strdup("genral");
		if (new->token == NULL || new->stat == NULL)
			(write(2, "error in allocation", 20), exit(1));
		new = parse_commands_2(&new, st);
		if (!new)
			return (NULL);
		new->nx = NULL;
	}
	else
		pars_word((char *)st, &new);
	return (new);
}

t_sh	*create_commands(char **words)
{
	t_sh	*head;
	t_sh	*node;
	int		i;

	if (!words || !*words)
		return (NULL);
	head = NULL;
	node = NULL;
	i = 0;
	while (words[i])
	{
		node = parse_commands_1(words[i]);
		if (!node)
			return (NULL);
		ft_lstadd_back(&head, node);
		i++;
	}
	return (head);
}

void	*parse_line(char *line)
{
	char	**shell_line;
	t_sh	*tok;
	// m_sh	*tok;

	shell_line = ft_split(line, ' ');
	tok = create_commands(shell_line);
	if (!tok)
		return (NULL);
	tok = pi_processing_cmd(&tok);
	// for (t_sh *tmp = ft_lstlast(&tok); tmp != NULL; tmp = tmp->pv)
	// {
	// 	printf("token [%s] --- type [%u] --- stat [%s]\n", tmp->token, tmp->type, tmp->stat);
	// }
	free_linked(&tok);
	puts("argement valid");
	exit(0);//scsses programe
}