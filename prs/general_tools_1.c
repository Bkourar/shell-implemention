#include "minishell.h"

int	ft_strcmp(char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && s2[j] && s1[i] == s2[j])
	{
		i++;
		j++;
	}
	return (s1[i] - s2[j]);
}

char	*join_whitout_quote(char const *s1, char const *s2)
{
	char	*string;
	int		i;
	int		j;

	j = 0;
	if (!s1 && !s2)
		return (string = NULL, NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	string = (char *)malloc(_ft_strlen(s1) + _ft_strlen(s2) + 2);
	if (!string)
		return (NULL);
	i = 0;
	while (s1[i] && !isquote(s1[i]))
		string[j++] = s1[i++];
	i = 0;
	while (s2[i])
		string[j++] = s2[i++];
	string[j] = '\0';
	return (string);
}

int	check_quote(char *str)
{
	int i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = is_quote(str[i]);
		if (j != 0)
			return (j);
		i++;
	}
	return (0);
}

char	*removed(char *str, char c, int b, t_env **env)
{
	char		**spl;
	int			i;
	int			j;

	spl = ft_split(str, c);
	j = count_wd(spl);
	free(str);
	str = NULL;
	i = -1;
	while (b == 0 && ++i < j)
	{
		str = ft_strjoin(str, spl[i]);
		if (!str)
			write(2, "fail allocation\n", 17), exit(1);
	}
	while (b == 1 && ++i < j)
	{
		str = ft_strjoin(str, expanding(spl[i], env));
		if (!str)
			write(2, "fail allocation\n", 17), exit(1);
	}
	return (free(spl), str);
}

char	*get_dolar(char *str)
{
	int		i;
	int		j;
	char	stack[500];

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			j++;
	}
	if (j % 2 == 0)
		return (str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\"')
			i++;
		stack[j++] = str[i];
		i++;
	}
	stack[j] = '\0';
	return (ft_strdup(stack));
}
