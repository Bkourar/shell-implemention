#include "minishell.h"

void	free_tsh(t_tk **likend)
{
	t_tk	*elem;
	t_tk	*tmp;

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

void	free_msh(t_sh **likend)
{
	t_sh	*elem;
	t_sh	*tmp;

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

void free_redirections(t_redir *red)
{
	t_redir *tmp;

	while (red)
	{
		tmp = red;
		red = red->next;
		free(tmp->file_name);
		free(tmp);
	}
}

void free_shell_list(t_sh *cmds)
{
	t_sh	*tmp;
	int		i;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		i = 0;
		while (tmp->args[i])
		{
			free(tmp->args[i]);
			i++;
		}
		free(tmp->args);
		free_redirections(tmp->dir);
		free(tmp);
	}
	cmds = NULL;
}

char	*check_and_dup(char c)
{
	char	*dst;

	dst = NULL;
	if (c == '\'')
		dst = ft_strdup("\'");
	else if (c == '\"')
		dst = ft_strdup("\'");
	if (!dst)
		write(2, "faile allocation\n", 18);
	return (dst);
}