#include "minishell.h"

int	long_nl(char const *str, char del)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (i);
	while (str[i] != del && str[i])
		i++;
	return (i);
}

int	str_cmp(char *buf, char *limiter)
{
	int	a;

	a = 0;
	if (limiter == NULL)
		return (0);
	while (buf[a] && buf[a] != '\n' && limiter[a] && limiter[a] == buf[a])
		a++;
	if (long_nl(limiter, '\0') == long_nl(buf, '\n')
		&& long_nl(limiter, '\0') == a)
		return (1);
	return (0);
}

void	pi_processing_here(int	fd, char *dilemiter, t_env **env, bool *b)
{
	char	*buff;
	pid_t	id;

	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == 0)
	{
		signal_heredoc();
		while (1)
		{
			buff = NULL;
			buff = readline("> ");
			if (buff == NULL || dilemiter[0] == '\0')
				break ;
			if (str_cmp(buff, dilemiter) == 1)
				break ;
			if (*b == false)
				buff = join_arg(pi_processing_expand(buff, env, false));
			write(fd, buff, long_nl(buff, '\n') + 1), write(fd, "\n", 1);
			free(buff);
		}
	}
	else if (id == -1)
		(perror("Fork failed"), exit(EXIT_FAILURE));
	(wait(NULL), ft_signal());
}

void	run_heredoc(char *arg, int i, t_tk **l)
{
	char	*dilemter;
	bool	logic;
	int		fd;
	int		j;

	logic = false;
	if (arg[i] == '<' && arg[i + 1] == '<')
	{
		j = i;
		dilemter = get_dilemter(arg, &i, &logic);
		if (!dilemter)
			write(2, "allocation fail4444\n", 21), exit(2);
		fd = open_here(dilemter, &(*l)->env, NULL, &logic);
		if (fd == -1)
			perror("OPEN: ");
	}
	else
		i += 1;
	if (arg[i] == '\0')
		return ;
	run_heredoc(arg, i, l);
}


char	*get_dilemter(char *inf, int *j, bool *logic)
{
	char	*stock;
	int		i;

	while (inf[*j] && (inf[*j] == ' ' || inf[*j] == '\t' || inf[*j] == '<'))
		*j += 1;
	allocation(&inf[*j], 0, &stock, 1);
	i = 0;
	while (inf[*j] != '\0' && inf[*j] != '|' && inf[*j] != ' ' && !check_dir(inf[*j]))
	{
		stock[i++] = inf[*j];
		*j += 1;
	}
	stock[i] = '\0';
	stock = diformer(stock, logic);
	return (stock);
}