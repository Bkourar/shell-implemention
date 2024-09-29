#include "minishell.h"

void	copy_gen(char *src, int *i, t_dir **lst)
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
    (dst[j] = '\0', owner_premt(&chmod, 0, 2, 0));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)), free(dst));
}

void	cin_singlq(char *src, int *i, t_dir **lst)
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
    (dst[j] = '\0', owner_premt(&chmod, 0, 2, 1));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)), free(dst));
	if (src[*i] && src[*i] == '\'')
		*i += 1;
}

void	expand_dir(char *arr, int *i, t_dir **lst)
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
    (dst[j] = '\0', owner_premt(&chmod, 4, 0, 0));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)), free(dst));
}

char	**mise_ajour_input(t_dir **lst)
{
	char	**data;
	t_dir	*tmp;
	int		i;

	data = (char **)malloc((ft_lstsiz_dir((*lst)) + 1) * sizeof(char *));
	if (!data)
		write(2, "faile allocation\n", 18), exit(1);
	i = 0;
	tmp = (*lst);
	while (tmp)
	{
		if (!ft_strcmp(tmp->input, """") || !ft_strcmp(tmp->input, "''"))
			tmp = tmp->next;
		else
		{
			data[i++] = ft_strdup(tmp->input);
			tmp = tmp->next;
		}
	}
	data[i] = 0;
	return (data);
}

void	upgrade_list(char **in, t_dir **lst)
{
	t_dir	*head;
	int		i;
	int		j;

	i = 0;
	head = NULL;
	while (in[i])
	{
		j = 0;
		if (in[i][0] == '$')
			expand_dir(in[i], &j, &head);
		else if (in[i][0] == '\"')
			parse_expand_dir(in[i], &j, &head);
		else if (in[i][0] == '\'')
			cin_singlq(in[i], &j, &head);
		else
			copy_gen(in[i], &j, &head);
		i++;
	}
	(*lst) = head;
	free_arr(in);
}
