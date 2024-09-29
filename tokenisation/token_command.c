#include "minishell.h"

t_tk	*parse_commands_2(t_tk **n, char const *string)
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

t_tk	*parse_commands_1(char const *st, t_env **env)
{
	t_tk	*new;

	new = NULL;
	if (!check_op(st[0]) && (st[1] == '\0' || check_redir(st)))
	{
		new = (t_tk *)malloc(sizeof(t_tk));
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

t_tk	*create_commands(char **words, t_env **env)
{
	t_tk	*head;
	t_tk	*node;
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

t_sh	*pi_processing_pro(char *str, t_sh **node, t_env **env)
{
	char		**cmd;
	t_sh		*new;
	int			i;

	new = (t_sh *) malloc(sizeof(t_sh));
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