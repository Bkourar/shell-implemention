#include "minishell.h"
#include "minishell1.h"

void	put_error(char *str)
{
	int	i;

	i = 0;
	write(1, "`", 1);
	while (str[i])
		write(2, &str[i++], 1);
	write(2, "'\n", 2);
}

void	synatx_error(char *str)
{
	write(2, "bash: syntax error near unexpected token ", 42);
	// printf("Error opening file: %s\n", strerror(errno)); 
	if (str[0] == '<' && str[1] == '<')
		put_error(str);
	else if (str[0] == '>' && str[1] == '>')
		put_error(str);
	else if (str[0] == '<')
		put_error(str);
	else if (str[0] == '>')
		put_error(str);
	else if (str[0] == '|')
		put_error(str);
	else if (str[0] == '\"')
		put_error(str);
	else if (str[0] == '\'')
		put_error(str);
	else
		put_error(str);
}

void	print_errors()
{
	write(2, "bash: syntax error near unexpected token `newline'\n", 52);
}

char	loop(t_sh **tmp, ee type, int *j)
{
	char c;

	while ((*tmp) != NULL && *j != 2)
	{
		if ((*tmp)->type == type)
		{
			c = (*tmp)->token[0];
			*j += 1;
		}
		(*tmp) = (*tmp)->nx;
	}
	return (c);
}

void	synatx_quotes(char c)
{
	write(2, "bash: unexpected EOF while looking for matching `", 50);
	write(2, &c, 1);
	write(2, "'\n", 2);
}
