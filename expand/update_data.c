#include "expand.h"

void	copy_input(char	*dst, char *src, int *i, t_state *st)
{
	int	j;

	j = 0;
	if (src[*i] && (src[*i] == '\"' || src[(*i + 1)] == '$'))
		*i += 2;
	else if (src[*i] && (src[*i] == '$' || is_numeric(src[(*i + 1)])))
		*i += 1;
	while (src[*i])
	{
		if (is_numeric(src[(*i - 1)]) && is_numeric(src[*i]))
			break ;
		if (!valid_expand(src[*i]))
		{
			break ;
		}
		dst[j++] = src[*i];
		*i += 1;
	}
	dst[j] = '\0';
	if (src[*i] == '\0' || src[*i] == ' ')
		*st = not_join;
	else
		*st = join;
}

static void	copy_whit_sq(char *dst, char *src, int *i, t_state *st)
{
	int	j;

	while (src[*i] && src[*i] == '\'')
		*i += 1;
	j = 0;
	while (src[*i])
	{
		if (src[*i] == '\'')
			break ;
		dst[j++] = src[*i];
		*i += 1;
	}
	dst[j] = '\0';
	while (src[*i] && src[*i] == '\'')
		*i += 1;
	if (src[*i] == '\0' || src[*i] == ' ')
		*st = not_join;
	else
		*st = join;
}

static void	copy_whit_dq(char *dst, char *src, int *i, t_state *st)
{
	int	j;

	while (src[*i] && src[*i] == '\"' && (src[(*i + 1)] && src[(*i + 1)] == '\"'))
		*i += 1;
	if (src[*i] && src[*i] == '\"')
		*i += 1;
	j = 0;
	while (src[*i])
	{
		if ((src[*i] == '\"' && src[(*i + 1)] != '\"') || src[*i] == '$')
		{
			*i += 1;
			break ;
		}
		dst[j++] = src[*i];
		*i += 1;
	}
	dst[j] = '\0';
	if (src[*i] == '\0' || src[*i] == ' ')
		*st = not_join;
	else
		*st = join;
}

void	copy_standard(char *dst, char *src, int *i, t_state *st)
{
	int	j;

	j = 0;
	while (src[*i])
	{
		if (src[*i] == '$' && (src[(*i + 1)] == '\'' || src[(*i + 1)] == '\"'))
			*i += 1;
		else if (j != 0 && (isquote(src[*i]) || src[*i] == '$' || src[*i] == ' '))
			break ;
		else
		{
			dst[j++] = src[*i];
			*i += 1;
		}
	}
	dst[j] = '\0';
	if (src[*i] == '\0' || src[*i] == ' ')
		*st = not_join;
	else
		*st = join;
}

t_exp	*update_input(char *in, t_exp **lst, bool b)
{
	t_exp	*head;
	char	*stack;
	t_state	st;
	t_type	tp;
	int		i;

	i = 0;
	st = not_join;
	tp = not_exp;
	printf("{%s}\n", in);
	while (in[i])
	{
		stack = (char *)ft_calloc(_ft_strlen(in) + 1, sizeof(char));
		if (!stack)
			write(2, "faile allocation\n", 18), exit(1);
		if (valid_condtion(in, i))
			(puts("1111"), copy_input(stack, in, &i, &st), upgrade_type(&tp, true));
		else if (in[i] == '\'')
			(puts("2222"), copy_whit_sq(stack, in, &i, &st), upgrade_type(&tp, false));
		else if (in[i] == '\"' && in[i + 1] != '$')
			(puts("3333"), copy_whit_dq(stack, in, &i, &st), upgrade_type(&tp, false));
		else
			(puts("4444"), copy_standard(stack, in, &i, &st) ,upgrade_type(&tp, false));
		(ft_lstadd_back_texp(lst, upgrade_input(stack, b, tp, st)), free(stack));
	}
	return (head = (*lst), head);
}
