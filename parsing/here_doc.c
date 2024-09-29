#include "minishell.h"

int	long_nl(char const *str, char del)
{
	int	i;

	i = 0;
	while (str[i] != del && str[i])
		i++;
	return (i);
}

int	str_cmp(char *buf, char *limiter)
{
	int	a;

	a = 0;
	while (buf[a] && buf[a] != '\n' && limiter[a] && limiter[a] == buf[a])
		a++;
	if (long_nl(limiter, '\0') == long_nl(buf, '\n')
		&& long_nl(limiter, '\0') == a)
		return (1);
	return (0);
}

void	pi_processing_here(int	fd, char *dilemiter, t_env **env)
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
			if (!buff)
				break ;
			if (str_cmp(buff, dilemiter) == 1)
				break ;
			if (!check_quote(dilemiter) && check_dolar(buff))
				buff = pi_processing_redirect(buff, env);
			write(fd, buff, long_nl(buff, '\n') + 1);
			free(buff);
		}
	}
	else if (id == -1)
		(perror("Fork failed"), exit(EXIT_FAILURE));
	(wait(NULL), ft_signal(), close(fd));
}

void	run_heredoc(char *arg, int i, t_tk **l)
{
	char	*dilemter;
	int		fd;
	int		j;

	if (arg[i] == '<' && arg[i + 1] == '<')
	{
		j = i;
		dilemter = get_dilemter(arg, &i);
		if (!dilemter)
			write(2, "allocation fail\n", 17), exit(2);
		dilemter = rand_rot13(dilemter);
		fd = open_here(dilemter, &(*l)->env);
		if (fd == -1)
			perror("OPEN: ");
	}
	else
		i += 1;
	if (arg[i] == '\0')
		return ;
	run_heredoc(arg, i, l);
}


char	*get_dilemter(char *inf, int *j)
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
	// stock = diformer(stock);
	return (stock);
}