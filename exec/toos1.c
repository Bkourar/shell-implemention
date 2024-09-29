#include "minishell.h"

void	ft_perror(char *str, int st)
{
	(void)st;
	int	i;

	i = 0;
	while(str[i])
	{
		write(2, &str, 1);
		i++;
	}
	exit(st);
}