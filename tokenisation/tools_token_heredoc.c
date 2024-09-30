#include "minishell.h"

void	std_copy(char *src, int *i, t_dir **lst)
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
		else if (j != 0 && isquote(src[*i]))
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

t_dir	*set_data(char *in, t_dir **lst)
{
	t_dir	*head;
	int		i;

	i = 0;
	while (in[i])
	{
		if (in[i] == '\'')
			puts("1"), copy_whit_singlq(in, &i, lst);
		else if (in[i] == '\"')
			puts("2"), copy_whit_doublq(in, &i, lst);
		else
			puts("3"), std_copy(in, &i, lst);
	}
	return (head = (*lst), head);
}

void	copyin_sqoute(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)malloc(sizeof(char) * _ft_strlen(src) + 1);
	if (!dst)
		write(2, "faile allocation\n", 18), exit(1);
	chmod = 0;
	j = 0;
	while (src[*i] && src[*i] != '\"')
	{
		if (j != 0 && src[*i] == '\'')
			break ;
		else
			dst[j++] = src[*i];
		*i += 1;
	}
	(dst[j] = '\0', owner_premt(&chmod, 0, 2, 1));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)), free(dst));
}

void	pars_whit_sq(char *src, int *i, t_dir **lst)
{
	while (src[*i] && src[*i] != '\"')
	{
		if (src[*i] == '\'')
			copy_singleq(src, i, lst);
		else
			copyin_sqoute(src, i, lst);
	}
}

void	copy_std_n(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)malloc(sizeof(char) * _ft_strlen(src) + 1);
	if (!dst)
		write(2, "faile allocation\n", 18), exit(1);
	chmod = 0;
	j = 0;
	while (src[*i] && src[*i] != '\"')
	{
		if (j != 0 && (src[*i] == '\''|| src[*i] == '$' || src[*i] == '\"'))
			break ;
		else
		{
			dst[j++] = src[*i];
			*i += 1;
		}
	}
	(dst[j] = '\0', owner_premt(&chmod, 0, 2, 1));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)), free(dst));
}
