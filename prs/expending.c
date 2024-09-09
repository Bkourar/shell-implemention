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

void	*ft_calloc(size_t nbr, size_t size)
{
	unsigned char	*buf;
	size_t	i;

	i = 0;
	buf = (unsigned char *)malloc(size * nbr);
	if (!buf)
		return (NULL);
	while (i < nbr * size)
	{
		buf[i] = 0;
		i++;
	}
	return ((void *)buf);
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

