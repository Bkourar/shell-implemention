#include "../prs/minishell.h"

int	ft_hrb(int flag, int stt)
{
	static int	x;

	if (flag == 1)
		x = stt;
	return (x);
}