#include "minishell.h"

static int mt_or_only_sp(char *str)
{
	if (!str)
		return (3);
	while(*str)
	{
		if (*str != ' ' && *str != '\t')
			return (22);
		str++;
	}
	return (3);
}

t_sh	*parse_commands_2(t_sh **n, char const *string)
{
	if (!ft_strcmp("<", string))
		(*n)->type = input;
	else if (!ft_strcmp(">", string))
		(*n)->type = output;
	else if (!ft_strcmp("<<", string))
		(*n)->type = heredoc;
	else if (!ft_strcmp(">>", string))
		(*n)->type = append;
	else if (checker_typing(string) > 0)
		complete_type(n, checker_typing(string));
	else if (!ft_strcmp("|", string))
		(*n)->type = Pipe;
	else if (!ft_strcmp("\"", string) || !ft_strcmp("'", string))
	{
		if (!ft_strcmp("\"", string))
			(*n)->type = d_quot;
		else
			(*n)->type = s_quot;
		(free((*n)->stat), (*n)->stat = ft_strdup("spicial"));
	}
	else if (!ft_strcmp("$", string))
		(*n)->type = dolar;
	return (*n);
}

t_sh	*parse_commands_1(char const *st, t_env **env)
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
		new->env = (*env); 
		new->nx = NULL;
	}
	else
		pars_word((char *)st, &new, env);
	return (new);
}

t_sh	*create_commands(char **words, t_env **env)
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
		node = parse_commands_1(words[i], env);
		if (!node)
			return (NULL);
		ft_lstadd_back_tsh(&head, node);
		i++;
	}
	return (head);
}

m_sh	*parse_line(char *line, m_sh **cmd, t_env **env)
{
	char	**shell_line;
	t_sh	*tok;

	if ((mt_or_only_sp(line)) == 3)
		return (NULL);
	shell_line = ft_split(line, ' ');
	if (!shell_line)
		return (write(2, "fail allocation\n", 17), NULL);
	tok = create_commands(shell_line, env);
	if (!tok)
		return (write(2, "fail allocation\n", 17), NULL);
	tok = pi_processing_cmd(&tok, line);
	if (!tok)
		return (NULL);
	free_tsh(&tok);
	(*cmd) = pi_processing_data(line, env);
	// printf("0 : %s\n", (*cmd)->args[0]);
	// printf("1 : %s\n", (*cmd)->args[1]);
	// printf("2 : %s\n", (*cmd)->args[2]);
	// printf("3 : %s\n", (*cmd)->args[3]);
	// printf("4 : %s\n", (*cmd)->args[4]);
	// printf("5 : %s\n", (*cmd)->args[5]);
	// exit(1);
	return (*cmd);
}
