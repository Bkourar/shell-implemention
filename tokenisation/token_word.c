#include "minishell.h"

void	up_grade(t_tk **n, char *string)
{
	if (!ft_strcmp("<<", string))
		(*n)->type = heredoc;
	else if (!ft_strcmp(">>", string))
		(*n)->type = append;
	else if (!ft_strcmp("<", string))
		(*n)->type = input;
	else if (!ft_strcmp(">", string))
		(*n)->type = output;
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
	else if (!ft_strcmp("|", string))
		(*n)->type = Pipe;
	else
		(*n)->type = word;
}

void up_date(char *str, t_tk **lst, t_env **env)
{
	t_tk	*node;

	if (!str)
	{
		printf("is NUALL");
	}
	node = ft_lstnew(str);
	node->stat = ft_strdup("general");
	if (!node->stat)
		(write(2, "error in allocation", 20), exit(1));
	up_grade(&node, str);
	if (!node || !node->token)
		(write(2, "error in allocation", 20), exit(1));
	node->env = (*env);
	ft_lstadd_back_tsh(&(*lst), node);
}

static void	take_str(char *str, int *i, t_tk **node, t_env **env)
{
	if (!str)
		write(2, "fail allocated\n", 16), exit(2);
	if (!ft_strcmp("<<", str))
		up_date(str, node, env), *i += 2;
	else if (!ft_strcmp(">>", str))
		up_date(str, node, env), *i += 2;
	else if (!ft_strcmp("<", str))
		up_date(str, node, env), *i += 1;
	else if (!ft_strcmp(">", str))
		up_date(str, node, env), *i += 1;
	else if (isquote(str[*i]))
	{
		up_date(check_and_dup(str[*i]), node, env);
		up_date(dup_quote(str, i, str[*i]), node, env);
		up_date(check_and_dup(str[*i]), node, env), *i += 1;
	}
	else if (!ft_strcmp("$", str))
		up_date(str, node, env), *i += 1;
	else if (!ft_strcmp("|", str))
		up_date(str, node, env), *i += 1;
	else
	{
		up_date(str, node, env);
		*i += ft_strlen(str);
	}
}

char	*get_word(char	*str)
{
	char	*stock;
	int		i;
	int		j;

	j = 0;
	while (check_op(str[j]) && str[j])
		j++;
	stock = (char *)malloc(sizeof(char) * j + 1);
	if (!stock)
		return (NULL);
	i = 0;
	while (check_op(str[i]) && str[i])
	{
		stock[i] = str[i];
		i++;
	}
	stock[i] = '\0';
	return (stock);
}

void	pars_word(char *input, t_tk **l, t_env **env)
{
	int		i = 0;

	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
			take_str(ft_strdup("<<"), &i, l, env);
		else if (input[i] == '>' && input[i + 1] == '>')
			take_str(ft_strdup(">>"), &i, l, env);
		else if (input[i] == '<')
			take_str(ft_strdup("<"), &i, l, env);
		else if (input[i] == '>')
			take_str(ft_strdup(">"), &i, l, env);
		else if (input[i] == '|')
			take_str(ft_strdup("|"), &i, l, env);
		else if (isquote(input[i]) && input[i + 1] != '\0')
			take_str(input, &i, l, env);
		else if (isquote(input[i]) && input[i + 1] == '\0')
			take_str(check_and_dup(input[i]), &i, l, env);
		else if (input[i] == '$')
			take_str(ft_strdup("$"), &i, l, env);
		else
			take_str(get_word(&input[i]), &i, l, env);
	}
}
