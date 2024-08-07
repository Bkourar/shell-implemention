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

void	pi_processing_here(int	fd, char *dilemiter)
{
	char	*buff;

	while (1)
	{
		write(1, " >", 2);
		buff = get_next_line(0);
		if (!buff)
			write(2, "allocation fail\n", 17), exit(2);
		if (str_cmp(buff, dilemiter) == 1)
			break ;
		// dup2(fd, STDOUT_FILENO);
		// if (close(fd) < 0)
		// 	(write(2, "close fail\n", 12), exit(2));
		write(fd, buff, long_nl(buff, '\n') + 1);
		free(buff);
	}
}

void	run_heredoc(char *arg, int i)
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
		pi_processing_here(fd, dilemter);
	}
	else
		i += 1;
	if (arg[i] == '\0')
		return ;
	run_heredoc(arg, i);
}
