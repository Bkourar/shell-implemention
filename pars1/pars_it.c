
#include "minishell.h"

void	ft_add_back(t_sh **lst, t_sh *new)
{
	t_sh	*temp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_word	*parse_word_2(t_word **list, char const *string)
{
	t_word	*new = (*list);

	if (!strcmp("<", string))
		new->type = strdup("input");
	else if (!strcmp(">", string))
		new->type = strdup("output");
	else if (!strcmp("<<", string))
		new->type = strdup("heredoc");
	else if (!strcmp(">>", string))
		new->type = strdup("append");
	else if (!strcmp("|", string))
		new->type = strdup("pipe");
	else if (!strcmp("\"", string) || !strcmp("'", string))
	{
		if (!strcmp("\"", string))
			new->type = strdup("d_quot");
		else
			new->type = strdup("s_quot");
		new->stat = strdup("spicial");
	}
	else if (!strcmp("$", string))
		new->type = strdup("dolar");
	else
		new->type = strdup("word");
	return (new);
}

t_word	*parse_word_1(char const *string)
{
	t_word	*new;

	new = (t_word *)malloc(sizeof(t_word));
	if (!new)
		return (NULL);
	new->token = strdup(string);
	if (new->token == NULL)
		(write(2, "error in allocation", 20), exit(1));
	new->stat = strdup("genral");
	if (new->token == NULL)
		(write(2, "error in allocation", 20), exit(1));
	new = parse_word_2(&new, string);
	if (!new ||!new->type || !new->token)
		return (NULL);
	return (new->next = NULL, new);
}

t_word *pars_pipe(char const *str)
{
	t_word *h;
	int		i;
	int		j;
	int		len;
	char 	*tmp;

	i = 0;
	h = (t_word *)malloc(sizeof(t_word));
	while(str[i] && h != NULL)
	{
		j = 0;
		len = 0;
		while(str[i + len] != '|' && str[i + len])
			len++;
		tmp = (char *)malloc(len + 1);
		while(str[i] != '|' && str[i])
			tmp[j++] = str[i++];
		(tmp[j] = '\0', ft_lstadd_back(&h, ft_lstnew(tmp)));
		if(str[i] == '|')
		{
			ft_lstadd_back(&h, ft_lstnew("|"));
			 i++;
		}
	}
	return (h);
}

t_word *pars_word(char const *str)
{
	t_word	*node = NULL;

	// node->stat = strdup("genral");
	// node->type = strdup("word");
	// if (!node->stat || !node->stat)
	// 	return (NULL);
	node = pars_pipe(str);
	if (!node)
		return (NULL);
	return (node);
}
