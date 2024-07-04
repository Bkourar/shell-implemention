#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include "minishell.h"

// 34-> " / 38-> & / 39-> ' / 36-> $ / 60-> < / 62-> > / 124-> | /

// int	syntax_error(char syntax_err)
// {
// 	if (syntx_er == 60 || syntx_er == 62 || syntx_er == 38 || syntx_er == 124 || syntx_er == 34 || syntx_er == 36)
// 			return (0);
// 	return (1);
// }

t_sh	*parse_commands_2(t_sh **list, char const *string)
{
	t_sh	*new = (*list);

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
	else if (!strcmp("'", string))
		new->type = strdup("s_t");
	else if (!strcmp("\"", string))
		new->type = strdup("d_quot");
	else if (!strcmp("$", string))
		new->type = strdup("dolar");
	else
	{
		new->word->token = strdup(string);
		if (!new->word->token || pars_word(new, string))
			return (NULL);
	}
	return (new);
}

t_sh	*parse_commands_1(char const *string)
{
	t_sh	*new;

	new = (t_sh *)malloc(sizeof(t_sh));
	if (!new)
		return (NULL);
	new->token = strdup(string);
	if (new->token == NULL)
		(write(2, "error in allocation", 20), exit(1));
	new->stat = strdup("genral");
	if (new->token == NULL)
		(write(2, "error in allocation", 20), exit(1));
	new = parse_commands_2(&new, string);
	if (!new)
		return (NULL);
	return (new->next = NULL, new);
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
		ft_add_back(&head, node);
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
	// printf("%s : %s\n",  tok->token, tok->type);
	for (t_sh *tmp = tok; tmp != NULL; tmp = tmp->next)
		printf("{%s} : [%s] : next-> \n", tmp->token, tmp->type);
	return (0);
}

// int line_error(char *line)
// {
// }