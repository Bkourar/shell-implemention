#include "../prs/minishell.h"

int	valid_exit(char *nbr)
{
	int	i;

	i = 0;
	while(nbr[i])
	{
		if (nbr[i] > '9' && nbr[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

int	ft_hrb(int flag, int stt)
{
	static int	x;

	if (flag == 1)
		x = stt;
	return (x);
}

void	ft_exit(m_sh *cmd)
{
	if (!cmd->args[1])
	{
		printf("exit\n");
		ft_hrb(1, 0);
	}
	if (cmd->args[1])
	{
		if (valid_exit(cmd->args[1]) == 0)
		{
			printf("exit : %s: numeric argument required\n", cmd->args[1]);
			ft_hrb(1, 255);
		}
		else if (valid_exit(cmd->args[2]))
		{
			printf("exit: too many arguments\n");
			ft_hrb(1, 1);
		}
	}
}
