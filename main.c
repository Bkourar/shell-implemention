#include "./prs/minishell.h"

void free_redirections(t_redir *red)
{
	t_redir *tmp;

	while (red)
	{
		tmp = red;
		red = red->next;
		free(tmp->file_name);
		free(tmp);
	}
}

void free_shell_list(m_sh *cmds)
{
	m_sh	*tmp;
	int		i;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		i = 0;
		while (tmp->args[i])
		{
			free(tmp->args[i]);
			i++;
		}
		free(tmp->args);
		free_redirections(tmp->dir);
		free(tmp);
	}
}

int main(int ac, char **av, char **env)
{
	char	*readit;
	m_sh	*cmd;
	t_env	*e;

	(void)ac, (void)av;
	e = parse_env(env);
	while (1)
	{
		readit = readline("\033[0;32m bash-1.$ \033[0;37m");
		if (fork() == 0)
		{
			cmd = parse_line(readit, &cmd, &e);
			if (!cmd)
				continue ;
			free_shell_list(cmd);
		}
		wait(NULL);
		// add_history(readit);
		// ft_start_exec(&cmd, &e);
		// cmd = NULL;
		free(readit);
	}
}
