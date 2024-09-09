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

	buff = NULL;
	while (1)
	{
		write(1, " >", 2);
		buff = readline(buff);
		if (!buff)
			continue;
		if (str_cmp(buff, dilemiter) == 1)
			break ;
		if (check_dolar(buff) && !check_quote(dilemiter))
		{
			buff = pi_process_expend(buff, env);
		}
		write(fd, buff, long_nl(buff, '\n') + 1);
		free(buff);
		buff = NULL;
	}
}

void	run_heredoc(char *arg, int i, t_sh **l, m_sh **s)
{
	char	*dilemter;
	int		fd;

	if (arg[i] == '<' && arg[i + 1] == '<')
	{
		dilemter = get_dilemter(arg, &i);
		if (!dilemter)
			write(2, "allocation fail\n", 17), exit(2);
		dilemter = rand_rot13(dilemter);
		fd = open_here(dilemter);
	if (!s)
		pi_processing_here(fd, dilemter, &(*l)->env);
	}
	else
		i += 1;
	if (arg[i] == '\0')
		return ;
	if (!s)
		run_heredoc(arg, i, l, NULL);
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
	return (stock);
}