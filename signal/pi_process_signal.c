# include "minishell.h"

static void	ctrl_c_newline(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_hrb(1, 0);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == SIGINT)
	{
		ft_hrb(1, 1);
		printf ("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signal()
{
	rl_catch_signals = 0;
	signal(SIGQUIT, ctrl_c_newline);
	signal(SIGINT, ctrl_c_newline);
}

static void	ctrl_c_line(int sig)
{
	if (sig == SIGQUIT)
	{
		puts("here");
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == SIGINT)
	{
		puts("hnanan");
		ft_hrb(1, 1);
		printf ("\n");
		exit(EXIT_FAILURE);
	}
}

void	signal_heredoc()
{
	signal(SIGQUIT, ctrl_c_line);
	signal(SIGINT, ctrl_c_line);
}
