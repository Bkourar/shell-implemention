#include "minishell.h"

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
	else if (checker_typing(string) > 0)
		complete_type(n, checker_typing(string));
	else if (!strcmp("|", string))
		(*n)->type = Pipe;
	else if (!strcmp("\"", string) || !strcmp("'", string))
	{
		if (!strcmp("\"", string))
			(*n)->type = d_quot;
		else
			(*n)->type = s_quot;
		(free((*n)->stat), (*n)->stat = ft_strdup("spicial"));
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
		new->token = ft_strdup(st);
		new->stat = ft_strdup("genral");
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
		ft_lstadd_back_tsh(&head, node);
		i++;
	}
	return (head);
}

void	parse_line(char *line)
{
	char	**shell_line;
	t_sh	*tok;

	shell_line = ft_split(line, ' ');
	if (!shell_line)
		write(2, "fail allocation\n", 17), exit(2);
	tok = create_commands(shell_line);
	if (!tok)
		write(2, "fail allocation\n", 17), exit(2);
	tok = pi_processing_cmd(&tok, line);
	// exit(0);//scsses programe
	free_tsh(&tok);
}
