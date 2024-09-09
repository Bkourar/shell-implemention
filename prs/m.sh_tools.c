#include "minishell.h"


void	ft_lstadd_redir(t_redir **lst, t_redir *new)
{
	t_redir	*temp;

	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	temp = (*lst);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void	ft_lstadd_back_msh(m_sh **lst, m_sh *new)
{
	m_sh	*temp;

	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	temp = (*lst);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	
}

t_redir	*creat_node(char *str, t_redir *node, t_env **env)
{
	// int		j;

	// if (check_dolar(str))
	// 	str = pi_process_expend(str, env);
	// else
	// {
	// 	if (check_quote(str) != 0)
	// 		str = removed(str);
	// }
	// if (!str)
	// 	(*node)->args[i] = ft_strdup("hello");///here is probelm exec
	if (node->tp == her_doc)
	{
		node->file_name = NULL;
		node->fd_her = open_here(str);
		pi_processing_here(node->fd_her, rand_rot13(str), env);
	}
	else
	{
		node->file_name = str;
		node->fd_her = -1;
	}
	node->next = NULL;
	return (node);
}

m_sh	*creat_commandline(m_sh **node, char *str, int *i, t_env **env)
{
	char	**spl;
	int			j;

	spl = pi_processing_expand(str, env, false);
	j = -1;
	while (spl[++j])
	{
		printf("{%s}\n", spl[j]);
		(*node)->args[*i] = ft_strdup(spl[j]);
		if (!(*node)->args[*i])
			return (NULL);
		*i += 1;
	}
	return (*node);
}

int	check_hash(char *str, int *i)
{
	int		j;
	int		b;
	int		save;

	j = 0;
	b = 0;
	save = *i;
	while (str[*i])
	{
		if (str[*i] == '\'')
			j++;
		if (str[*i] == '$')
			b++;
		if (b == 2 || str[*i] == '\"' || j == 2)
			break ;
		*i += 1;
	}
	*i = save;
	return (j);
}