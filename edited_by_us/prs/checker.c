#include "minishell.h"
#include "minishell1.h"


int	check_dir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	check_type(t_e i)
{
	if (i == in || i == out || i == app || i == her_doc)
		return (i);
	return (0);
}

int	isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int check_op(char c)
{
	if (!(c == '<' || c == '>' || c == '$' || c == '|' || c == '\"' || c == '\''))
		return (1);
	return (0);
}

int check_op1(ee i)
{
	if (i == input || i == output || i == append || i == heredoc)
		return (1);
	return (0);
}


// int	check_pipe(char *str, int j, int i)
// {
// 	int		counter;
// 	char	c;

// 	counter = 0;
// 	while (str[i])
// 	{
// 		if (isquote(str[i]) && counter == 0)
// 		{
// 			c = str[i];
// 			counter++, i++;
// 			while (str[i] && str[i] != c)
// 			{
// 				if (i == j)
// 					return (1);
// 				i++;
// 			}
// 			if (str[i] && str[i] == c)
// 				counter++;
// 		}
// 		if (counter == 2)
// 			counter = 0;
// 		i++;
// 	}
// 	return (0);
// }

// m_sh	*creat_commandline(m_sh **node, char *str, int i)
// {
// 	(*node)->args[i] = ft_strdup(str);
// 	if (!(*node)->args[i])
// 		return (NULL);
// 	free(str);
// 	return (*node);
// }

// m_sh	*pi_processing_pro(char *str, m_sh **node)
// {
// 	char	**cmd;
// 	m_sh	*new;
// 	int		i;
// 	int		j;

// 	new = (m_sh *) malloc(sizeof(m_sh));
// 	if (!new)
// 		return (NULL);
// 	cmd = ft_split(str, ' ');
// 	if (!cmd || !(*cmd))
// 		return (NULL);
// 	j = 0;
// 	i = 0;
// 	while (cmd[j])
// 		j++;
// 	new->args = (char **)malloc(sizeof(char *) * (j + 1));
// 	if (!new->args)
// 		return (NULL);
// 	while (cmd[i])
// 	{
// 		new = creat_commandline(&new, cmd[i], i);
// 		i++;
// 	}
// 	new->args[i] = 0;
// 	return (new->dir = (*node)->dir, new->next = NULL, new);
// }
