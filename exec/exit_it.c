#include "minishell.h"

int	ft_hrb(int flag, int stt)
{
	static int	x;

	if (flag == 1)
		x = stt;
	return (x);
}

int	valid_exit(char *str)
{
	while (*str && (*str == '\t' || *str == ' '))
		str++;
	if (*str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!(*str >= '0' && *str <= '9'))
		return (0);
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	while (*str && (*str == '\t' || *str == ' '))
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

void	ft_exit(t_sh *cmd)
{
	ft_putstr_x("exit\n", NULL, NULL, 2);
	if (!cmd->args[1])
		exit(ft_hrb(1, 0));
	else
	{
		if (valid_exit(cmd->args[1]) == 0)
		{
			ft_putstr_x("exit :",
				cmd->args[1], ": numeric argument required\n", 2);
			exit(ft_hrb(1, 255));
		}
		else if (cmd->args[2])
		{
			ft_putstr_x("exit: too many arguments\n", NULL, NULL, 2);
			ft_hrb(1, 1);
		}
		else
			exit(atoll_x(cmd->args[1]));
	}
}
