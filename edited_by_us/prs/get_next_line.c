#include "minishell.h"

char	*f_insial(void)
{
	char	*new;
	size_t	i;

	i = 0;
	new = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!new)
		return (NULL);
	while (i < (size_t)BUFFER_SIZE)
		new[i++] = '\0';
	new[i] = '\0';
	return (new);
}

char	*start(char *arr, int fd)
{
	char	*buf;
	int		c;

	c = 1;
	if (!arr)
	{
		arr = ft_strdup("");
		if (!arr)
			return (NULL);
	}
	buf = f_insial();
	if (!buf)
		return (free(arr), NULL);
	while (arr && c > 0 && check_nl(arr) == -1)
	{
		c = read(fd, buf, BUFFER_SIZE);
		if (c == -1)
			return (free(arr), free(buf), NULL);
		if (c > 0)
			arr = f_strjoin(arr, buf, c);
	}
	return (free(buf), buf = NULL, arr);
}

char	*by_line(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(i + 1);
	if (!line)
		return (NULL);
	while (++j < i)
		line[j] = str[j];
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*new_buf;

	if ((fd < 0 || fd >= OPEN_MAX) || BUFFER_SIZE <= 0
		|| (read(fd, NULL, 0) == -1))
		return (free(str), str = NULL, NULL);
	if (!check_nl(str))
		str = start(str, fd);
	new_buf = by_line(str);
	str = free_line(str);
	if (!new_buf || *new_buf == '\0')
	{
		free(str);
		free(new_buf);
		return (str = NULL, NULL);
	}
	return (new_buf);
}
