#include "../prs/minishell.h"

static int n_option(char *str)
{
	if (str && *str == '-')
	{
		str++;
		if (*str != 'n')
			return (0);
		while (*str)
		{
			if (*str != 'n')
				return (0);
			str++;
		}
		return (1);
	}
	return (0);
}


void	build_echo(char **args, int i)
{
	int	flg;

	flg = 1337;
	if (args[1])
	{
		while(n_option(args[i]))
		{
			flg = 42;
			i++;
		}
		while(args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
	}
	if (flg == 1337)
		printf("\n");
}
