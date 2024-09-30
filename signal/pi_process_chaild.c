#include "minishell.h"

static void	ctrl_nline_quit(int sig)
{
	if (sig == SIGINT)
		(printf ("\n"), ft_hrb(1, 130));
	else if (sig == SIGQUIT)
		(printf("Quit: %d\n", sig), ft_hrb(1, 131));
}

void	signal_child()
{
	signal(SIGQUIT, ctrl_nline_quit);
	signal(SIGINT, ctrl_nline_quit);
}
