#include "minishell.h"

int		ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while(s[i])
		i++;
	return (i);
}