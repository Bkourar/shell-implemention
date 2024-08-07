#include "minishell.h"

int	check_nl(char const *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\n')
	{
		if (str[i] == '\0')
			return (-1);
		i++;
	}
	return (i);
}

char	*f_strjoin(char *str1, char *str2, int line_b)
{
	char	*dest;
	int		i;
	int		j;

	i = -1;
	j = -1;
	dest = (char *)malloc (ft_strlen(str1) + line_b + 1);
	if (!dest || !str2)
		return (free(str1), str1 = NULL, NULL);
	while (str1[++i])
		dest[i] = str1[i];
	while (++j < line_b)
		dest[i + j] = str2[j];
	dest[i + j] = '\0';
	return (free(str1), dest);
}

char	*free_line(char *back_buf)
{
	char	*next_buf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!back_buf)
		return (NULL);
	while (back_buf[i] && back_buf[i] != '\n')
		i++;
	if (back_buf[i] == '\n')
		i++;
	while (back_buf[i + j])
		j++;
	next_buf = (char *) malloc(j + 1);
	if (!next_buf)
		return (free(back_buf), back_buf = NULL, NULL);
	j = 0;
	while (back_buf[i])
		next_buf[j++] = back_buf[i++];
	next_buf[j] = '\0';
	free (back_buf);
	if (*next_buf == '\0')
		return (free(next_buf), next_buf = NULL, NULL);
	return (next_buf);
}

char	*get_dilemter(char *inf, int *j)
{
	char	*stock;
	int		i;

	while (inf[*j] && (inf[*j] == ' ' || inf[*j] == '\t' || inf[*j] == '<'))
		*j += 1;
	allocation(&inf[*j], 0, &stock, 1);
	i = 0;
	while (inf[*j] != '\0' && inf[*j] != '|' && inf[*j] != ' ' && !check_dir(inf[*j]))
	{
		stock[i++] = inf[*j];
		*j += 1;
	}
	stock[i] = '\0';
	return (stock);
}