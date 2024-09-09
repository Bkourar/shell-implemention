#include "minishell.h"

void	allocation(char *src, size_t l, char **dst, int type)
{
	if (type == 1 && l == 0)
	{
		while (src[l] && src[l] != '|' && src[l] != ' ' && !check_dir(src[l]))
			l++;
	}
	dst[0] = (char *)malloc((sizeof(char) * l) + 1);
	if (!dst[0])
		write(2, "fail allocatin\n", 15), exit(1);
}

char	*ft_strncpy(char *dst, char *src, int index)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (src[i] && i < (unsigned int)index)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

int	count_wd(char **spliting)
{
	int	i;

	i = 0;
	if (!spliting)
		return (0);
	while (spliting[i])
		i++;
	return (i);
}

char	*check_sq(char *str)
{
	char	stack[255];
	int		i;
	int		j;
	int		l;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '#')
		{
			j = 1;
			break ;
		}
	}
	i = -1;
	l = 0;
	while (j == 1 && str[++i])
	{
		if (str[i] != '#' && str[i] != '\'')
			stack[l++] = str[i];
	}
	stack[l] = '\0';
	return (free(str), ft_strdup(stack));
}

void	change_hastag(char *c1, char *c2, int *j, int *i)
{
	*c1 = '\'';
	*c2 = '#';
	*j += 2;
	*i += 1;
}