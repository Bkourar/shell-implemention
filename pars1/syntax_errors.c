#include "minishell.h"
// #include <errno.h> 

void	put_error(char *str)
{
	int	i;

	i = 0;
	write(1, "`", 1);
	while (str[i])
		write(2, &str[i++], 1);
	write(2, "'\n", 2);
	exit(1);
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
	exit(1);
}

