#include "minishell.h"

void	build_echo(char **args, int i);
int		n_option(char *str);

void	build_echo(char **args, int i)
{
	int	flg;

	flg = 1337;
	if (args[1])
	{
		while (n_option(args[i]))
		{
			flg = 42;
			i++;
		}
		while (args[i])
		{
			ft_putstr_x(args[i], NULL, NULL, 1);
			if (args[i + 1])
				ft_putstr_x(" ", NULL, NULL, 1);
			i++;
		}
	}
	if (flg == 1337)
		ft_putstr_x("\n", NULL, NULL, 1);
}

int	n_option(char *str)
{
	if (str && *str == '-')
	{
		str++;
		if (*str != 'n')
			return (0);
		while (*str)
		{
			if (*str != 'n')
				return (0);
			str++;
		}
		return (1);
	}
	return (0);
}

