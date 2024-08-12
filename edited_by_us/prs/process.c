#include "minishell.h"

m_sh	*pi_processing_pro(char *str, m_sh **node)
{
	char	**cmd;
	m_sh	*new;
	int		i;
	int		j;

	new = (m_sh *) malloc(sizeof(m_sh));
	if (!new)
		return (NULL);
	cmd = ft_split(str, ' ');
	if (!cmd || !(*cmd))
		return (NULL);
	j = 0;
	i = 0;
	while (cmd[j])
		j++;
	new->args = (char **)malloc(sizeof(char *) * (j + 1));
	if (!new->args)
		return (NULL);
	while (cmd[i])
	{
		new = creat_commandline(&new, cmd[i], i);
		i++;
	}
	new->args[i] = 0;
	return (new->dir = (*node)->dir, new->next = NULL, new);
}

t_sh	*pi_processing_cmd(t_sh **lst, char *str)
{
	t_sh	*tmp;
	char	c1;
	char	c2;
	int		i;

	tmp = (*lst);
	while (tmp != NULL)
	{
		c1 = tmp->token[0];
		c2 = tmp->token[1];
		if (tmp->type == err)
			pi_processing_err_3(lst, &tmp, c1, c2, str);
		tmp = tmp->nx;
	}
	tmp = ft_lstlast(lst);
	if (tmp->type == L_err && !check_herepipe(lst))
		(run_heredoc(str, 0), synatx_error(tmp->token));
	else if (tmp->type == L_err && check_herepipe(lst) != 0)
		synatx_error(tmp->token);
	pi_processing_err_1(lst, &tmp, str);//pipe
	pi_processing_err_2(lst, str);//direction
	pi_processing_err_4((*lst), 0, str);//quote
	pi_processing_err_5(lst, str);//echo
	return (tmp);
}

