#include "./builtin/builtin.h"
#include "./parse/minishell.h"

static int mt_or_only_sp(char *str)
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

int main()
{
	char	*readit;
	m_sh	*cmd;
	while (1)
	{
		readit = readline("\033[0;32m bash-1.$ \033[0;37m");
		if (mt_or_only_sp(readit) == 3)
			continue;
		if (fork() == 0)
			parse_line(readit);
        wait(NULL);
        cmd = pi_processing_data(readit);
//		(wait(NULL), free(readit));
		
		
			
		 free(readit);
	}
}
