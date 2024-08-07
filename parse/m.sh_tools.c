#include "minishell.h"
#include "minishell1.h"


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

t_redir	*creat_node(char *str,t_redir *node)
{
	if (node->tp == her_doc)
	{
		node->file_name = NULL;
		node->fd_her = open_here(str);
		pi_processing_here(node->fd_her, rand_rot13(str));
	}
	else
	{
		node->file_name = str;
		node->fd_her = -1;
	}
	node->next = NULL;
	return (node);
}

m_sh	*creat_commandline(m_sh **node, char *str, int i)
{
	(*node)->args[i] = ft_strdup(str);
	if (!(*node)->args[i])
		return (NULL);
	free(str);
	return (*node);
}