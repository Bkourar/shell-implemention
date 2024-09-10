#include "expand.h"

int	valid_expand(char c)
{
	if (is_numeric(c) || c == '_' || is_alpha(c))
		return (1);
	return (0);
}

char	**pi_processing_expand(char *str, t_env **env, bool b)
{
	t_exp	*head;
	char	**spl;
	t_exp	*tp;

	head = NULL;
	head = update_input(str, &head, b);
	search_and_replace(&head, env, 0);
	tp = head;
	while (tp)
	{
		// if (tp->input[0] != '\0')
			printf("[%s]", tp->input);
		// else
		// 	puts("sjel");
		if (tp->state == join)
			printf("  :  join\n");
		else
			printf("  :  not_join\n");
		tp = tp->next;
	}
	exit(2);
	spl = ft_split(join_expand(&head), ' ');
	return (spl);
}

int		check_dolar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	check_space(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	ft_lstsiz_exp(t_exp *lst)
{
	int		i;
	t_exp	*node;

	node = lst;
	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}