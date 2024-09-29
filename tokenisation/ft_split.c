#include "minishell.h"

int	count_word(char const *string, char c)
{
	int	count_w;
	int	i;

	i = 0;
	count_w = i;
	while (string[i])
	{
		while (string[i] == c && string[i])
			i++;
		if (string[i] && string[i] != c)
			count_w++;
		while (string[i] && string[i] != c)
			i++;
	}
	return (count_w);
}

int	len_strings(char const *string, char c)
{
	int	len_w;
	int	i;

	i = 0;
	len_w = 0;
	while (string[i] == c && string[i])
		i++;
	while (string[i + len_w] != c && string[i + len_w])
		len_w++;
	return (len_w);
}

static char	**dynamic(char const *src, char c)
{
	char	**str;
	int		count;

	if (!src)
		return (NULL);
	count = count_word(src, c) + 1;
	str = (char **) malloc (count * sizeof(char *));
	if (!str)
		return (NULL);
	return (str);
}

static char	**free_str(char **str, int count)
{
	while (--count >= 0)
		free(str[count]);
	free (str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		k;

	str = dynamic(s, c);
	if (!str)
		return (NULL);
	i = 0;
	k = -1;
	while (++k < count_word(s, c))
	{
		j = 0;
		str[k] = (char *)malloc((len_strings(&s[i], c) + 1) * sizeof(char));
		if (!str[k])
			return (free_str(str, k));
		while (s[i] && s[i] == c)
			i++;
		while (s[i] != c && s[i])
			str[k][j++] = s[i++];
		str[k][j] = '\0';
	}
	str[k] = 0;
	return (str);
}
