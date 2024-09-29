#include "minishell.h"

void	copy_expanse(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		j;
	int		chmod;

	if (src[*i] && (src[*i] == '$' || is_numeric(src[(*i + 1)])))
		*i += 1;
	j = 0;
	dst = (char *)malloc(sizeof(char) * _ft_strlen(src) + 1);
	if (!dst)
		write(2, "faile allocation\n", 18), exit(1);
	dst[j++] = '$';
	chmod = 0;
	while (src[*i])
	{
		if (is_numeric(src[(*i - 1)]) && is_numeric(src[*i]))
			break ;
		if (!valid_expand(src[*i]))
			break ;
		dst[j++] = src[*i];
		*i += 1;
	}
	(dst[j] = '\0', owner_premt(&chmod, 4, 0, 0));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)), free(dst));
}

void	copy_whit_singlq(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		j;
	int		chmod;

	dst = (char *)malloc(sizeof(char) * _ft_strlen(src) + 1);
	if (!dst)
		write(2, "faile allocation\n", 18), exit(1);
	chmod = 0;
	j = 0;
	while (src[*i])
	{
		if (j != 0 && src[*i] == '\'')
			break ;
		dst[j++] = src[*i];
		*i += 1;
	}
	dst[j++] = '\'';
	(dst[j] = '\0', owner_premt(&chmod, 0, 2, 1));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)), free(dst));
	if (src[*i] == '\'')
		*i += 1;
}

void	copy_whit_doublq(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		j;
	int		chmod;

	dst = (char *)malloc(sizeof(char) * _ft_strlen(src) + 1);
	if (!dst)
		write(2, "faile allocation\n", 18), exit(1);
	chmod = 0;
	j = 0;
	while (src[*i])
	{
		if (j != 0 && src[*i] == '\"')
			break ;
		dst[j++] = src[*i];
		*i += 1;
	}
	dst[j++] = '\"';
	(dst[j] = '\0', owner_premt(&chmod, 4, 2, 1));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)), free(dst));
	if (src[*i] == '\"')
		*i += 1;
}

void	copy_std_dfl(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		j;
	int		chmod;

	dst = (char *)malloc(sizeof(char) * _ft_strlen(src) + 1);
	if (!dst)
		write(2, "faile allocation\n", 18), exit(1);
	chmod = 0;
	j = 0;
	while (src[*i])
	{
		if (src[*i] == '$' && (src[(*i + 1)] == '\'' || src[(*i + 1)] == '\"'))
			*i += 1;
		else if (j != 0 && (isquote(src[*i]) || src[*i] == '$'))
			break ;
		else if (white_sp(src[*i]))
			break;
		else
		{
			dst[j++] = src[*i];
			*i += 1;
		}
	}
	(dst[j] = '\0', owner_premt(&chmod, 0, 2, 0));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)), free(dst));
}

t_dir	*analyse_input(char *in, t_dir **lst)
{
	t_dir	*head;
	int		i;

	i = 0;
	while (in[i])
	{
		if (valid_condtion(in, i))
			copy_expanse(in, &i, lst);
		else if (in[i] == '\'')
			copy_whit_singlq(in, &i, lst);
		else if (in[i] == '\"')
			copy_whit_doublq(in, &i, lst);
		else
			copy_std_dfl(in, &i, lst);
	}
	return (head = (*lst), head);
}