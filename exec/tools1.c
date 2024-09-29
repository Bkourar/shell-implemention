#include "minishell.h"

int			ft_in_range(long long nb);
long long	atoll_x(char *str);
void		ft_perror(char *str, int st);
void		ft_putstr_x(char *s1, char *s2, char *s3, int fd);

int	ft_in_range(long long nb)
{
	if (nb > LLONG_MAX || nb < LLONG_MIN)
	{
		return (0);
	}
	return (1);
}

long long	atoll_x(char *str)
{
	int			sign;
	long long	res;
	int			i;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	if (ft_in_range(res * sign))
		return (res * sign);
	ft_putstr_x("exit :", str, ": numeric argument required\n", 2);
	exit(ft_hrb(1, 255));
}

void	ft_perror(char *str, int st)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str, 1);
		i++;
	}
	exit(st);
}

void	ft_putstr_x(char *s1, char *s2, char *s3, int fd)
{
	if (s1)
	{
		while (*s1)
		{
			write(fd, s1, 1);
			s1++;
		}
	}
	if (s2)
	{
		while (*s2)
		{
			write(fd, s2, 1);
			s2++;
		}
	}
	if (s3)
	{
		while (*s3)
		{
			write(fd, s3, 1);
			s3++;
		}
	}
}
