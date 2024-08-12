#include "./prs/minishell.h"

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

	cmd = NULL;
	while (1)
	{
		readit = readline("\033[0;32m bash-1.$ \033[0;37m");
		if (mt_or_only_sp(readit) == 3)
			continue;
		cmd = parse_line(readit, &cmd);
		int i = 0;
		while(cmd)
		{
			i = 0;
			while(cmd->args[i])
			{
				printf("%s\n", cmd->args[i]);
				i++;
			}
			printf("\nnew one \n");
			cmd = cmd->next;
		}
		 free(readit);
	}
}
