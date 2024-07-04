#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>

int		count_word(char const *string, char c);
char	**ft_split(char const *s, char c);

typedef struct command_line
{
	char				*token;
	char				*type;
	struct command_line	*next;
}						t_sh;

int	ft_lstsize(t_sh *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

// 34-> " / 38-> & / 39-> ' / 36-> $ / 60-> < / 62-> > / 124-> | /

// int	syntax_error(char syntax_err)
// {
// 	if (syntx_er == 60 || syntx_er == 62 || syntx_er == 38 || syntx_er == 124 || syntx_er == 34 || syntx_er == 36)
// 			return (0);
// 	return (1);
// }

t_sh	*parse_commands_2(t_sh **list, char const *string)
{
	t_sh	*new;

	new = (*list);
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
		new->type = strdup("s_quot");
	else if (!strcmp("\"", string))
		new->type = strdup("d_quot");
	else if (!strcmp("$", string))
		new->type = strdup("dolar");
	else
		new->type = strdup("word");
	return (new->next = NULL, new);
}

t_sh	*parse_commands_1(t_sh **list, char const *string)
{
	t_sh	*new;

	new = (t_sh *)malloc(sizeof(t_sh));
	if (!new)
		return (NULL);
	new->token = strdup(string);
	if (new->token == NULL)
		(write(2, "error in allocation", 20), exit(1));
	new = parse_commands_2(&new, string);
	if (!new)
		return (NULL);
	return (new->next = NULL, new);
}

t_sh	*create_commands(char **words, int number_arg)
{
	t_sh	*head;
	t_sh	*node;
	int		i;
	int		j;

	head = NULL;
	node = NULL;
	i = -1;
	while (words[++i])
	{
		node = parse_commands_1(&head, words[i]);
		node->next = head;
		head = node;
	}
	return (head);
}

int parse_line(char *line)
{
	char	**shell_line;
	t_sh	*tok;
	int		i;
	int		j;

	shell_line = ft_split(line, ' ');
	if (!shell_line)
		return (1);
	tok = create_commands(shell_line, count_word(line, ' '));
	if (!tok)
		return (1);
	for (t_sh *tmp = tok; tmp != NULL; tmp = tmp->next)
		printf("{%s} : [%s] : next-> \n", tmp->token, tmp->type);
	return (0);
}

// int line_error(char *line)
// {
// }

int main()
{
	char	*readit;
	while (1)
	{
		readit = readline("\033[0;32m bash-1.$ \033[0;37m");
		if (parse_line(readit))
			(free(readit), write(2, "bash: syntax error near unexpected token \n", 43), exit(1));
		free(readit);
	}
}