#include "minishell.h"

static void	ctrl_nline_quit(int sig)
{
	if (sig == SIGINT)
		printf ("\n");
	else if (sig == SIGQUIT)
		printf("Quit: %d\n", sig);
}

void	signal_child()
{
	signal(SIGQUIT, ctrl_nline_quit);
	signal(SIGINT, ctrl_nline_quit);
}
