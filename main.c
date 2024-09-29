#include "minishell.h"

static int mt_or_only_sp(char *str)
{
	if (!str)
		return (3);
	while(*str)
	{
		if (!white_sp(*str))
			return (22);
		str++;
	}
	return (3);
}

t_sh	*parse_line(char *line, t_sh **cmd, t_env **env)
{
	char	**shell_line;
	t_tk	*tok;
	t_sh	*head;

	if ((mt_or_only_sp(line)) == 3)
		return (NULL);
	shell_line = ft_split(line, ' ');
	if (!shell_line)
		return (write(2, "fail allocation\n", 17), NULL);
	tok = create_commands(shell_line, env);
	if (!tok)
		return (write(2, "fail allocation\n", 17), NULL);
	tok = pi_processing_cmd(&tok, line);
	if (!tok)
		return (NULL);
	free_tsh(&tok);
	head = NULL;
	(*cmd) = pi_processing_data(line, env, &head);
	if (!(*cmd))
		return (NULL);
	return (*cmd);
}

int main(int ac, char **av, char **env)
{
	char	*readit;
	t_sh	*cmd;
	t_env	*e;
	struct termios termios;

	((void)ac, (void)av, ft_signal());
	e = parse_env(env);
	tcgetattr(STDIN_FILENO, &termios);
	while (1)
	{
		rl_catch_signals = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &termios);
		readit = readline("bash-1.2$ ");
		if (!readit)
			break ;
		add_history(readit);
		cmd = parse_line(readit, &cmd, &e);
		if (!cmd)
			continue ;
		(ft_start_exec(&cmd, &e), free_shell_list(cmd), free(readit));
		cmd = NULL;
	}
	printf("exit\n");
}
