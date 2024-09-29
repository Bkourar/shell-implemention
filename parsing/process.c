#include "minishell.h"

t_tk	*pi_processing_cmd(t_tk **lst, char *str)
{
	t_tk	*tmp;
	char	c1;
	char	c2;

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
		return (run_heredoc(str, 0, lst), synatx_error(tmp->token), NULL);
	else if (tmp->type == L_err && check_herepipe(lst) != 0)
		return (synatx_error(tmp->token), NULL);
	if (pi_processing_err_1(lst, &tmp, str) || pi_processing_err_2(lst, str))
		return (NULL);
	else if (pi_processing_err_4(lst, 0, str) || pi_processing_err_5(lst, str))
		return (NULL);
	return (tmp);
}

int	is_alpha(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	check_redir(char const *str)
{
	if (!ft_strcmp(str, "<<") || !ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

int check_op1(ee i)
{
	if (i == input || i == output || i == append || i == heredoc)
		return (1);
	return (0);
}

char	*dup_quote(char *str, int *i, char c)
{
	char	*dst;
	int		j;

	dst = (char *)malloc(sizeof(char) * (_ft_strlen(&str[*i]) + 1));
	if (!dst)
		write(2, "faile allocation\n", 18), exit(1);
	if (str[*i] == c)
		*i += 1;
	j = 0;
	while (str[*i])
	{
		if (str[*i] == c)
			break ;
		dst[j++] = str[*i];
		*i += 1;
	}
	return (dst[j] = '\0', dst);
}
