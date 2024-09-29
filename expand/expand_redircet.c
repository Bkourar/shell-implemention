#include "minishell.h"

void	expand_wqoute(char *arr, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	if (arr[*i] && (arr[*i] == '$' || is_numeric(arr[(*i + 1)])))
		*i += 1;
	dst = (char *)malloc(sizeof(char) * _ft_strlen(arr) + 1);
	if (!dst)
		write(2, "faile allocation\n", 18), exit(1);
	chmod = 0;
	j = 0;
	while (arr[*i])
	{
		if (is_numeric(arr[(*i - 1)]) && is_numeric(arr[*i]))
			break ;
		if (!valid_expand(arr[*i]))
			break ;
		dst[j++] = arr[*i];
		*i += 1;
	}
	(dst[j] = '\0', owner_premt(&chmod, 4, 2, 1));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)), free(dst));
}

void	copy_in_sqoute(char *src, int *i, t_dir **lst)
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
	(dst[j] = '\0', owner_premt(&chmod, 0, 2, 1));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)), free(dst));
}

void	copy_singleq(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)malloc(sizeof(char) *  2);
	if (!dst)
		write(2, "faile allocation\n", 18), exit(1);
	chmod = 0;
	j = 0;
	if (src[*i] == '\'')
		dst[j++] = src[*i];
	(dst[j] = '\0', owner_premt(&chmod, 0, 0, 1));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)), free(dst));
	*i += 1;
}

void	parsse_wesq(char *src, int *i, t_dir **lst)
{
	while (src[*i] && src[*i] != '\"')
	{
		if (src[*i] == '\'')
			copy_singleq(src, i, lst);
		else if (valid_condtion(src, *i))
			expand_wqoute(src, i, lst);
		else
			copy_in_sqoute(src, i, lst);
	}
}

void	copy_std_norm(char *src, int *i, t_dir **lst)
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