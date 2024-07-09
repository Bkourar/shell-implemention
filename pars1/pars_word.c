#include "minishell.h"

void	up_grade(t_sh **n, char *string)
{
	if (!strcmp("<<", string))
		(*n)->type = strdup("heredoc");
	else if (!strcmp(">>", string))
		(*n)->type = strdup("append");
	else if (!strcmp("<", string))
		(*n)->type = strdup("input");
	else if (!strcmp(">", string))
		(*n)->type = strdup("output");
	else if (!strcmp("\"", string) || !strcmp("'", string))
	{
		if (!strcmp("\"", string))
			(*n)->type = strdup("d_quot");
		else
			(*n)->type = strdup("s_quot");
		(free((*n)->stat), (*n)->stat = strdup("spicial"));
	}
	else if (!strcmp("$", string))
		(*n)->type = strdup("dolar");
	else if (!strcmp("|", string))
		(*n)->type = strdup("pipe");
	else
		(*n)->type = strdup("word");
}

void up_date(char *str, t_sh **lst)
{
	t_sh	*node;

	node =  ft_lstnew(str);
	node->stat = strdup("general");
	if (!node->stat)
		(write(2, "error in allocation", 20), exit(1));
	up_grade(&node, str);
	if (!node || !node->token || !node->type)
		(write(2, "error in allocation", 20), exit(1));
	ft_lstadd_back(&(*lst), node);
}

void	take_str(char *string, int *i, t_sh **node)
{
	if (!strcmp("<<", string))
		up_date(string, node), *i += 2;
	else if (!strcmp(">>", string))
		up_date(string, node), *i += 2;
	else if (!strcmp("<", string))
		up_date(string, node), *i += 1;
	else if (!strcmp(">", string))
		up_date(string, node), *i += 1;
	else if (!strcmp("\"", string))
		up_date(string, node), *i += 1;
	else if (!strcmp("'", string))
		up_date(string, node), *i += 1;
	else if (!strcmp("$", string))
		up_date(string, node), *i += 1;
	else if (!strcmp("|", string))
		up_date(string, node), *i += 1;
	else
	{
		up_date(string, node);
		*i += strlen(string);
	}
}

char	*get_word(char	*str)
{
	int		i;
	char	stock[255];

	i = 0;
	while (check_op(str[i]) && str[i])
	{
		stock[i] = str[i];
		i++;
	}
	stock[i] = '\0';
	return (strdup(stock));
}

void	pars_word(char *input, t_sh **l)
{
	int		i = 0;

	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
			take_str(strdup("<<"), &i, l);
		else if (input[i] == '>' && input[i + 1] == '>')
			take_str(strdup(">>"), &i, l);
		else if (input[i] == '<')
			take_str(strdup("<"), &i, l);
		else if (input[i] == '>')
			take_str(strdup(">"), &i, l);
		else if (input[i] == '|')
			take_str(strdup("|"), &i, l);
		else if (input[i] == '\"')
			take_str(strdup("\""), &i, l);
		else if (input[i] == '\'')
			take_str(strdup("'"), &i, l);
		else if (input[i] == '$')
			take_str(strdup("$"), &i, l);
		else
			take_str(get_word(&input[i]), &i, l);
	}
}
