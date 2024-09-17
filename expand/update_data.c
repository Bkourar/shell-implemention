#include "expand.h"

void	copy_input(char *src, int *i, t_exp **lst)
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
	(dst[j] = '\0', premission(&chmod, 4, 0, 0));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, false, &chmod)), free(dst));
}

void	copy_whit_sq(char *src, int *i, t_exp **lst)
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
	(dst[j] = '\0', premission(&chmod, 0, 0, 0));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, false, &chmod)), free(dst));
	if (src[*i] == '\'')
		*i += 1; 
}

void	copy_whit_dq(char *src, int *i, t_exp **lst)
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
	(dst[j] = '\0', premission(&chmod, 4, 0, 0));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, false, &chmod)), free(dst));
	if (src[*i] == '\"')
		*i += 1;
}

void	copy_standard(char *src, int *i, t_exp **lst)
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
	(dst[j] = '\0', premission(&chmod, 0, 0, 0));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, false, &chmod)), free(dst));
}

t_exp	*update_input(char *in, t_exp **lst)
{
	t_exp	*head;
	int		i;

	i = 0;
	while (in[i])
	{
		if (valid_condtion(in, i))
			copy_input(in, &i, lst);
		else if (in[i] == '\'')
			copy_whit_sq(in, &i, lst);
		else if (in[i] == '\"')
			copy_whit_dq(in, &i, lst);
		else if (white_sp(in[i]))
			skip_wspace(in, &i, lst);
		else
			copy_standard(in, &i, lst);
	}
	return (head = (*lst), head);
}
