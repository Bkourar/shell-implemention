#include "minishell.h"

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