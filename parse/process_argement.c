#include "minishell.h"
#include "minishell1.h"

t_redir	*get_token(char *inf, t_redir **l)
{
	char	*stock;
	int		i;
	int		j;

	i = 0;
	j = 0;
	(*l) = (t_redir *)malloc(sizeof(t_redir));
	if (!(*l))
		write(2, "allocation fail", 16), exit(1);
	if (inf[j] == '>' && inf[j + 1] == '>')
		(*l)->tp = app;
	else if (inf[j] == '<' && inf[j + 1] == '<')
		(*l)->tp = her_doc;
	else if (inf[j] == '<' && !check_dir(inf[j + 1]))
		(*l)->tp = in;
	else if (inf[j] == '>' && !check_dir(inf[j + 1]))
		(*l)->tp = out;
	else
		return (free(*l), NULL);
	while (inf[j] && (inf[j] == ' ' || inf[j] == '\t' || check_dir(inf[j])))
		j++;
	allocation(&inf[j], 0, &stock, 1);
	while (inf[j] != '\0' && inf[j] != '|' && inf[j] != ' ' && !check_dir(inf[j]))
		stock[i++] = inf[j++];
	return (stock[i] = '\0', creat_node(stock, (*l)));
}

t_redir	 *get_token_dir(char *str, t_redir **lin)
{
	t_redir	*new;
	int		i;

	i = 0;
	new = NULL;
	while (str[i])
	{
		new = get_token(&str[i], &new);
		if (!new)
			i++;
		else
		{
			ft_lstadd_redir(lin, new);
			if (new->tp == out || new->tp == in)
				i++;
			else if (new->tp == her_doc || new->tp == app)
				i += 2;
			if (new->file_name != NULL)
				i += ft_strlen(new->file_name);
			else
				i += 2;
		}
	}
	return (*lin);
}

char	*pi_processing_dir(char *str, m_sh **h_n)
{
	char	stack[255];
	t_redir	*head;
	int		i;
	int		j;

	head = NULL;
	head = get_token_dir(str, &head);
	(*h_n) = (m_sh *)malloc(sizeof(m_sh));
	if (!(*h_n))
		write(2, "allocation fail", 16), exit(1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (i != 0 && str[i] == ' ' && check_dir(str[i - 1]))
			i += replace_space(stack, &j, &str[i]);
		else if (i != 0 && !check_dir(str[i]) && check_dir(str[i - 1]))
			i += replace_space(stack, &j, &str[i]);
		if (check_dir(str[i]) || str[i] == ' ')
			stack[j++] = ' ', i++;
		else
			stack[j++] = str[i++];
	}
	return ((*h_n)->dir = head, stack[j] = '\0', ft_strdup(stack));
}

m_sh	*update_argement(char *cmd, m_sh **new_n, int index)
{
	char	stack[255];
	char	*k;
	char	*l;

	l = ft_strncpy(stack, cmd, index);
	k  = pi_processing_dir(l, new_n);
	(*new_n) = pi_processing_pro(k, new_n);
	free(k);
	return (*new_n);
}

void	pi_processing_data(char *str)
{
	m_sh	*head;
	m_sh	*new;
	int		i;
	m_sh	*tmp = NULL;

	i = -1;
	head = NULL;
	new = NULL;
	while (str[++i])
	{
		if (str[i] == '|' && !check_pipe(str, i, 0))
		{
			new = update_argement(str, &new, i);
			ft_lstadd_back_msh(&head, new);
			str = restory_cmd(str);
			i = -1;
		}
		else if (str[i] != '|' && str[i + 1] == '\0')
		{
			new = update_argement(str, &new, i + 1);
			ft_lstadd_back_msh(&head, new);
		}
	}
	tmp = head;
	int x ;
	while(tmp)
	{
		x  = 0;
		while(tmp->args[x])
		{
			while(tmp->dir)
			{
				printf(" type %u -------- file %s\n", tmp->dir->tp, tmp->dir->file_name);
				tmp->dir = tmp->dir->next;
			}
			printf("cmd  : %s\n",  tmp->args[x]);
			x++;
		}
		tmp = tmp->next;
	}
	puts("argement valid");
	exit(0);
}


	// printf("[cmd : %s]\n",tmp->args[0]);
	// printf("[arg : %s]\n",tmp->args[1]);
	// printf("[name : %s]---[fd : %d]---[tp : %u]\n", tmp->dir->file_name, tmp->dir->fd_her, tmp->dir->tp);
	// printf("[name : %s]---[fd : %d]---[tp : %u]\n", tmp->dir->next->file_name, tmp->dir->next->fd_her, tmp->dir->next->tp);
	// tmp = tmp ->next;
	// printf("[cmd : %s]\n",tmp->args[0]);
	// printf("[arg : %s]\n",tmp->args[1]);
	// printf("[name : %s]---[fd : %d]---[tp : %u]\n", tmp->dir->file_name, tmp->dir->fd_her, tmp->dir->tp);
	// printf("[name : %s]---[fd : %d]---[tp : %u]\n", tmp->dir->next->file_name, tmp->dir->next->fd_her, tmp->dir->next->tp);
	// tmp = tmp ->next;
	// printf("[cmd : %s]\n",tmp->args[0]);
	// printf("[arg : %s]\n",tmp->args[1]);
	// printf("[name : %s]---[fd : %d]---[tp : %u]\n", tmp->dir->file_name, tmp->dir->fd_her, tmp->dir->tp);
	// printf("[name : %s]---[fd : %d]---[tp : %u]\n", tmp->dir->next->file_name, tmp->dir->next->fd_her, tmp->dir->next->tp);
