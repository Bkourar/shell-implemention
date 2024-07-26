#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct command_line
{
	char				*token;
	char				*type;
	char				*stat;
	struct command_line	*nx;
}						t_s;


typedef struct s_data
{
	t_s	*cmds;
}	t_data;

t_data	*get_data(t_data *to_save)
{
	static t_data	*saved;

	if (to_save != NULL)
		saved = to_save;
	return (saved);
}

// t_s	*get_data(t_s *to_save);
// t_s		*head = NULL;

t_s	*ft_lstnew(char *content)
{
	t_s	*n_node;
	int	i  = -1;

	n_node = malloc(sizeof(t_s));
	if (!n_node)
		return (NULL);
	n_node->token = strdup(content);
	n_node->nx = NULL;
	return (n_node);
}

void	ft_lstadd_back(t_s **lst, t_s *new)
{
	t_s	*temp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->nx)
		temp = temp->nx;
	temp->nx = new;
}

void	up_grade(t_s **n, char *string)
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
		(*n)->type = strdup("Pipe");
	else
		(*n)->type = strdup("word");
}

void	up_date(char *str)
{
	t_s	*head;

	// head = get_data(NULL)->cmds;
	// ft_lstadd_back(&get_data(NULL)->cmds, ft_lstnew(str));
	
	head = ft_lstnew(str);
	head->stat = strdup("general");
	if (!head->stat)
		(write(2, "error in allocation", 20), exit(1));
	up_grade(&head, str);
	if (!head || !head->token || !head->type)
	(write(2, "error in allocation", 20), exit(1));
	ft_lstadd_back(&get_data(NULL)->cmds, head);
	// for (t_s *tmp = head; tmp != NULL; tmp = tmp->nx)
	// {
	// 	printf("token [%s] ---- type [%s] ---- stat [%s]\n", tmp->token, tmp->type, tmp->stat);
	// }
}

void	take_str(char *string, int *i)
{
	if (!strcmp("<<", string))
		up_date(string), *i +=  2;
	else if (!strcmp(">>", string))
		up_date(string), *i +=  2;
	else if (!strcmp("<", string))
		up_date(string), *i += 1;
	else if (!strcmp(">", string))
		up_date(string), *i += 1;
	else if (!strcmp("\"", string))
		up_date(string), *i += 1;
	else if (!strcmp("'", string))
		up_date(string), *i += 1;
	else if (!strcmp("$", string))
		up_date(string), *i += 1;
	else if (!strcmp("|", string))
		up_date(string), *i += 1;
	else
	{
		up_date(string);
		*i += strlen(string);
	}
}

int check_op(char c)
{
	if (!(c == '<' || c == '>' || c == '$' || c == '|' || c == '$' || c == '\"' || c == '\''))
		return (1);
	return (0);
}

char	*get_word(char	*str)
{
	int		i;
	int		j;
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

void	pars(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
			take_str(strdup("<<"), &i);
		else if (input[i] == '>' && input[i + 1] == '>')
			take_str(strdup(">>"), &i);
		else if (input[i] == '<')
			take_str(strdup("<"), &i);
		else if (input[i] == '>')
			take_str(strdup(">"), &i);
		else if (input[i] == '|')
			take_str(strdup("|"), &i);
		else if (input[i] == '\"')
			take_str(strdup("\""), &i);
		else if (input[i] == '\'')
			take_str(strdup("'"), &i);
		else if (input[i] == '$')
			take_str(strdup("$"), &i);
		else
			take_str(get_word(&input[i]), &i);
	}
}


int main(int ac, char **av)
{
	int		i;
	int		j;
	char	*input;
	t_data	data;
	
	data.cmds = NULL;

	get_data(&data);
	while (1)
	{
		input = readline("\033[0;32m bash-1.$ \033[0;37m");
		pars(input);
		for (t_s *tmp = data.cmds; tmp != NULL; tmp = tmp->nx)
		{
			printf("token [%s] ---- type [%s] ---- stat [%s]\n", tmp->token, tmp->type, tmp->stat);
		}
		free(input);
	}
}
