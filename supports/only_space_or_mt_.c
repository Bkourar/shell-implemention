int mt_or_only_sp(char *str)
{
	if (!str)
		return (3);
	while(*str)
	{
		if (*str != ' ' && *str != '\t')
			return (22);
		str++;
	}
	return (3);
}
/*
int main()
{
	char	*readit;
	while (1)
	{
		readit = readline("\033[0;32m bash-1.$ \033[0;37m");
		if (mt_or_only_sp(readit) == 3)//!!!!!
		{
			continue ;
		}
		if (parse_line(readit))
			(free(readit), write(2, "bash: syntax error near unexpected token \n", 43), exit(1));
		free(readit);
	}
}
*/