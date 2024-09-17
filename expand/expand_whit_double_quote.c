#include "expand.h"

void	copy_std(char *src, int *i, t_exp **lst)
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
	(dst[j] = '\0', premission(&chmod, 0, 0, 1));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, false, &chmod)), free(dst));
}

void	copy_in_sq(char *src, int *i, t_exp **lst)
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
		if (j != 0 && (src[*i] == '\'' || src[*i] == '$'))
			break ;
		else
			dst[j++] = src[*i];
		*i += 1;
	}
	(dst[j] = '\0', premission(&chmod, 0, 0, 1));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, false, &chmod)), free(dst));
}

void	parsse_sq(char *src, int *i, t_exp **lst)
{
	while (src[*i] && src[*i] != '\"')
	{
		if (src[*i] == '\'')
			copy_single_q(src, i, lst);
		else if (valid_condtion(src, *i))
			expand_sq(src, i, lst);
		else
			copy_in_sq(src, i, lst);
	}
}

void	parssing_expand(char *src, int *i, t_exp **head)
{
	if (src[*i] && src[*i] == '\"')
		*i += 1;
	while (src[*i] && src[*i] != '\"')
	{
		if (src[*i] == '$' && is_numeric(src[(*i + 1)]))
			i += 2;
		else if (valid_condtion(src, *i))
			expand_sq(src, i, head);
		else if (src[*i] == '\'')
			parsse_sq(src, i, head);
		else
			copy_std(src, i, head);
	}
	if (src[*i] && src[*i] == '\"')
		i += 1;
}

void	copy_general(char *src, int *i, t_exp **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)malloc(sizeof(char) * _ft_strlen(src) + 1);
	if (!dst)
		write(2, "faile allocation\n", 18), exit(1);
	chmod = 0;
	j = 0;
	while (src[*i])
	{
		dst[j++] = src[*i];
		*i += 1;
	}
	(dst[j] = '\0', premission(&chmod, 0, 0, 0));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, false, &chmod)), free(dst));
}