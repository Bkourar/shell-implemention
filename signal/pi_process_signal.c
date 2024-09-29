# include "minishell.h"

static void	ctrl_c_newline(int sig)
{
	(void)sig;
	printf ("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal()
{
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_newline);
}

static void	ctrl_c_line(int sig)
{
	(void)sig;
	printf ("\n");
	exit(EXIT_FAILURE);
}

void	signal_heredoc()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_line);
}
