#include "minishell.h"

char	*give_arg(t_env **env, t_exp *l, char ***in)
{
	t_env	*tp;

	(*in) = (char **)malloc((1 + 1) * sizeof(char *));
	if (!(*in))
		write(2, "faile allocation\n", 18), exit(1);
	tp = (*env);
	while (tp)
	{
		if (!ft_strcmp(l->input, tp->var))
			break ;
		tp = tp->next;
	}
	return (ft_strdup(tp->value));
}

char	*give_status(char *str)
{
	if (!ft_strcmp(str, "?"))
		return (ft_strdup("statuz"));
	return (ft_strdup("$"));
}

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
	}
	if (i != 0 && valid_expand(str[i - 1]) && valid_expand(str[i + 1]))
		return (1);
	return (0);
}

int	condition_for_split(t_exp **hd)
{
	t_exp	*tp;

	if ((*hd) != NULL || (*hd)->prv != NULL || (*hd)->next != NULL)
		return (0);
	tp = (*hd);
	if (tp->prv->input[0] == '=' && tp->next->input[0] == '=')
		return (0);
	else if (tp->prv->input[0] == '=' && tp->prv->set->tp == not_exp)
		return (0);
	else if (tp->next->input[0] == '=' && tp->next->set->tp == not_exp)
		return (0);
	else if (check_equal(tp->input))
		return (0);
	return (1);
}

char	**parse_value(t_exp **hd, t_env **env)
{
	char	**spl;
	t_env	*tp;

	tp = (*env);
	while (tp)
	{
		if (!ft_strcmp((*hd)->input, tp->var))
		{
			if (condition_for_split(&(*hd)))
				return (spl[0] = give_arg(env, (*hd), &spl), spl[1] = 0, spl);
			spl = ft_split(tp->value, ' ');
			if (!spl)
				write(2, "faile allocation\n", 18), exit(1);
			return (spl);
		}
		tp = tp->next;
	}
	spl = (char **)malloc((1 + 1) * sizeof(char *));
	if (!spl)
		write(2, "faile allocation\n", 18), exit(1);
	else if (tp == NULL && (!ft_strcmp((*hd)->input, "?") || !ft_strcmp((*hd)->input, "$")))
		return (spl[0] = give_status((*hd)->input), spl[1] = 0, spl);
	else
		return (spl[0] = ft_strdup("\0"), spl[1] = 0, spl);
	return (free_arr(spl), NULL);
}

void	autortion(char **s, t_exp **l, int rwx, bool b)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 2;
	k = 0;
	while (s[i])
	{
		if (j % 2 == 0)
		{
			ft_lstadd_back_texp(l, upgrade_input(s[i], b, &rwx));
			i++;
		}
		else
		{
			ft_lstadd_back_texp(l, upgrade_input(" ", b, &k));
		}
		j++;
	}
}
