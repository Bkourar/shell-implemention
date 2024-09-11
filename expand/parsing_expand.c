#include "expand.h"

char	*expand_whit_dq(char *in, t_exp **lst)
{
	char	stack;
	t_type	*tp;
	int		i;

	i = 0;
	*tp = not_exp;
	while (in[i])
	{
		stack = (char *)malloc(_ft_strlen(in) * sizeof(char) + 1);
		if (!stack)
			write(2, "faile allocation\n", 18), exit(1);
		if (valid_condtion(in, i, false))
			(copy_input(stack, in, &i, lst), upgrade_type(&tp, true));
		else if (in[i] == '\'')
			(copy_whit_sq(stack, in, &i, lst), upgrade_type(&tp, false));
		else
			(copy_standard(stack, in, &i, lst) ,upgrade_type(&tp, false));
		(ft_lstadd_back_texp(lst, upgrade_input(stack, false, tp)), free(stack));
	}
}

int	condition_expand(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (str[i] == '$' && valid_expand(str[i + 1]))
			return (1);
		i++;
	}
	return (0);
}