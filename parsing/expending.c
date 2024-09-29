#include "minishell.h"

int	is_numeric(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	change_space(char *c1, char *c2, int *j, int *i)
{
	*c1 = '\'';
	*c2 = '\'';
	*j += 2;
	*i += 2;
}

void	change_dbq(char *c1, char *c2, int *j, int *i)
{
	*c1 = '\'';
	*c2 = '$';
	*j += 2;
	*i += 2;
}

int	check_expend(char c1, char c2)
{
	if (c1 == '$' && c2 == '$')
		return (1);
	if (c1 == '$' && isquote(c2))
		return (1);
	if (c1 == '$' && is_numeric(c2))
		return (1);
	return (0);
}

char	*join_arg(char **spl)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (spl[i])
	{
		str = ft_strjoin(str, spl[i]);
		i++;
	}
	return (str);
}