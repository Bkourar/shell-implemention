#include "minishell.h"
#include "minishell1.h"

char	*rand_rot13(char *path)
{
	int		i;

	i = 0;
	while (path[i])
	{
		if ((path[i] >= 'a' && path[i] < 'm') || (path[i] >= 'A' && path[i] < 'M'))
			path[i] = path[i] + 13;
		else if ((path[i] >= 'n' && path[i] < 'z') || (path[i] >= 'N' && path[i] < 'Z'))
			path[i] = path[i] - 13;
		i++;
	}
	return (path);
}

char	*restory_cmd(char *src)
{
	char	*stock;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '|' && !check_pipe(src, i, 0))
		{
			i++;
			stock = (char *)malloc(ft_strlen(&src[i]) + 1);
			if (!stock)
				return (NULL);
			while (src[i])
				stock[j++] = src[i++];
			stock[j] = '\0';
			break ;
		}
		i++;
	}
	return (ft_strdup(stock));
}

int	open_here(char *del)
{
	static char	*c;
	int			fd;

	c = rand_rot13(del);
	c = ft_strjoin("/tmp", c);
	fd = open(c, O_CREAT | O_WRONLY, 777);
	if (fd == -1)
		puts("here"), perror("OPEN: ");
	if (unlink(c) == -1)
		perror("UNLINK: ");
	free(c);
	return (fd);
}

int	replace_space(char *dst, int *i, char *src)
{
	int	j;

	j = 0;
	while (src[j] && (src[j] == ' ' || src[j] == '\t' || check_dir(src[j])))
		j++;
	while (src[j])
	{
		if (src[j] == ' ' || check_dir(src[j]))
			break;
		dst[*i] = ' ';
		j++;
		*i += 1;
	}
	return (j);
}
