#include "minishell.h"

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

int	open_here(char *del, t_env **env)
{
	char	*c;
	int		fd = 0;

	c = rand_rot13(del);
	c = join_path("/tmp", c);
	if (access(c, F_OK) == 0)
	{
		c[0] = 'a';
		c[4] = 'm';
		c[5] = 'z';
		open_here(c, env);
	}
	else
	{
		fd = open(c, O_CREAT | O_WRONLY , 0777);
		if (fd == -1)
			perror("OPEN: ");
		pi_processing_here(fd, del, env), close(fd);
		fd = open(c, O_RDONLY, 0444);
	}
	if (unlink(c) == -1)
		perror("UNLINK: ");
	return (free(c), fd);
}

static int rpl_str_quote(char *dst, int *i, char *str, char c)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (j != 0 && str[j] == c)
		{
			j++;
			break ;
		}
		dst[*i] = ' ';
		*i += 1;
		j++;
	}
	if (str[j - 1] == c)
	{
		dst[*i] = ' ';
		*i += 1;
	}
	return (j);
}

int	replace_space(char *dst, int *i, char *src)
{
	int	j;

	j = 0;

	while (src[j] && (white_sp(src[j]) || check_dir(src[j])))
		j++;
	if (src[j] == '\'' || src[j] == '\"')
		return (rpl_str_quote(dst, i, &src[j], src[j]) + j);
	while (src[j])
	{
		if (white_sp(src[j]) || check_dir(src[j]))
			break;
		dst[*i] = ' ';
		j++;
		*i += 1;
	}
	return (j);
}
