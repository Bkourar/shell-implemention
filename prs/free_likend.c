#include "minishell.h"

void	free_tsh(t_sh **likend)
{
	t_sh	*elem;
	t_sh	*tmp;

	if (likend == NULL)
		return ;
	if (*likend == NULL)
	{
		free((*likend)->token);
		free((*likend)->stat);
		free(*likend);
		return ;
	}
	elem = *likend;
	while (elem->nx != NULL)
	{
		tmp = elem->nx;
		free(elem->token);
		free(elem->stat);
		free(elem);
		elem = tmp;
	}
	free(elem);
}

void	free_msh(m_sh **likend)
{
	m_sh	*elem;
	m_sh	*tmp;

	if (likend == NULL)
		return ;
	if (*likend == NULL)
	{
		free((*likend)->args[0]);
		free((*likend)->args[1]);
		free((*likend)->dir->file_name);
		free((*likend)->dir);
		free((*likend));
		return ;
	}
	elem = *likend;
	while (elem->next != NULL)
	{
		tmp = elem->next;
		free(elem->dir->file_name);
		free(elem->args[0]);
		free(elem->args[1]);
		free(elem->dir), free(elem);
		elem = tmp;
	}
	free(elem);
}

char	*remove_db_quote(char *str)
{
	char	*cpy;
	int		i;
	int		j;

	cpy = (char *)ft_calloc(_ft_strlen(str) * 2, sizeof(char));
	if (!cpy)
		return (write(2, "allocation fail\n", 17), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			cpy[j++] = '\'';
			i++;
		}
		else
			cpy[j++] = str[i++];
	}
	return (removed(cpy, '\'', 0, NULL));
}

int	is_alpha(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}