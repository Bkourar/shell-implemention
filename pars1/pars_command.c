#include "minishell.h"

t_sh	*ft_shell_last(t_sh **lst)
{
	t_sh	*tmp;

	if (!lst)
		return (NULL);
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_sh	*parse_commands_2(t_sh **list, char const *string)
{
	t_sh	*n = (*list);

	if (!strcmp("<", string))
		n->type = strdup("input");
	else if (!strcmp(">", string))
		n->type = strdup("output");
	else if (!strcmp("<<", string))
		n->type = strdup("heredoc");
	else if (!strcmp(">>", string))
		n->type = strdup("append");
	else if (!strcmp("|", string))
		n->type = strdup("pipe");
	else if (!strcmp("\"", string) || !strcmp("'", string))
	{
		if (!strcmp("\"", string))
			n->type = strdup("d_quot");
		else
			n->type = strdup("s_quot");
		(free(n->stat), n->stat = strdup("spicial"));
	}
	else if (!strcmp("$", string))
		n->type = strdup("dolar");
	return (n);
}

t_sh	*parse_commands_1(char const *string)
{
	t_sh	*new;

	new = NULL;
	if (!check_op(string[0]))
	{
		new = (t_sh *)malloc(sizeof(t_sh));
		if (!new)
			return(NULL);
		new->token = strdup(string);
		new->stat = strdup("genral");
		if (new->token == NULL || new->stat == NULL)
			(write(2, "error in allocation", 20), exit(1));
		new = parse_commands_2(&new, string);
		if (!new ||!new->type)
			return (NULL);
		new->next = NULL;
	}
	else
		pars_word((char *)string, &new);
	return (new);
}

t_sh	*create_commands(char **words)
{
	t_sh	*head;
	t_sh	*node;
	int		i;

	head = NULL;
	node = NULL;
	i = -1;
	while (words[++i])
	{
		node = parse_commands_1(words[i]);
		if (!node)
			return (puts("333"), NULL);
		ft_lstadd_back(&head, node);
	}
	return (head);
}

int parse_line(char *line)
{
	char	**shell_line;
	t_sh	*tok;

	shell_line = ft_split(line, ' ');
	if (!shell_line)
		return (1);
	tok = create_commands(shell_line);
	if (!tok)
		return (1);
	//here test all agrement li habiti abro
	// for (t_sh *tmp = tok; tmp != NULL; tmp = tmp->next)
	// {
	// 	printf("token [%s] --- type [%s] --- stat [%s]\n", tmp->token, tmp->type, tmp->stat);
	// }
	return (0);
}