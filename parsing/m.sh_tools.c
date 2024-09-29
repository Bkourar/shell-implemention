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

void	ft_lstadd_back_msh(t_sh **lst, t_sh *new)
{
	t_sh	*temp;

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
	if (node->tp == her_doc)
	{
		node->file_name = NULL;
		str = rand_rot13(str);
		node->fd_her = open_here(str, env);
		pi_processing_here(node->fd_her, str, env);
	}
	else
	{
		if (str == NULL)
			node->file_name = NULL;
		else
			node->file_name = str;
		node->fd_her = -1;
	}
	node->next = NULL;
	return (node);
}

t_sh	*creat_commandline(t_sh **node, char *str, int *i)
{
	(*node)->args[*i] = ft_strdup(str);
	if (!(*node)->args[*i])
		return (NULL);
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