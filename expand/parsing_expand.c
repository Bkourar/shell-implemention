#include "expand.h"

int	condition_expand(char *str)
{

	if (str[0] == '$' && valid_expand(str[1]))
		return (1);
	return (0);
}

void	expand(char *arr, int *i, t_exp **lst)
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
		dst[j++] = arr[*i];
		*i += 1;
	}
	(dst[j] = '\0', premission(&chmod, 4, 0, 0));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, false, &chmod)), free(dst));
}

void	expand_sq(char *arr, int *i, t_exp **lst)
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
	(dst[j] = '\0', premission(&chmod, 4, 0, 1));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, false, &chmod)), free(dst));
}

void	copy_single_q(char *src, int *i, t_exp **lst)
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
	(dst[j] = '\0', premission(&chmod, 0, 0, 1));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, false, &chmod)), free(dst));
	*i += 1;
}

void	cin_singl_q(char *src, int *i, t_exp **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	if (src[*i] && src[*i] == '\'')
		*i += 1;
	dst = (char *)malloc(sizeof(char) * _ft_strlen(src) + 1);
	if (!dst)
		write(2, "faile allocation\n", 18), exit(1);
	chmod = 0;
	j = 0;
	while (src[*i])
	{
		if (j != 0 && src[*i] == '\'')
			break ;
		else
			dst[j++] = src[*i];
		*i += 1;
	}
	(dst[j] = '\0', premission(&chmod, 0, 0, 1));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, false, &chmod)), free(dst));
	if (src[*i] && src[*i] == '\'')
		*i += 1;
}
