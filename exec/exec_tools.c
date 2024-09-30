#include "minishell.h"

void	main_exec(t_data *dt, t_sh *cmd, t_env *env, char **path);
void	final_ex(t_sh *cmd, t_env *env, char *pth);
void	deal_with_chp(t_data *dt, t_sh *cmd, char *pth, t_env *env);
void	deal_with_pp(t_data *dt, t_sh *cmd);

void	main_exec(t_data *dt, t_sh *cmd, t_env *env, char **path)
{
	char	*pth;

	pth = get_path(path, cmd->args[0]);
	if (cmd->next && pipe(dt->fd) == -1)
	{
		write(2, "pipe", 5);
		exit(ft_hrb(1, 127));
	}
	signal_child();
	dt->pids[dt->i] = fork();
	if (dt->pids[dt->i] < 0)
	{
		write(2, "fork", 5);
		exit(ft_hrb(1, 127));
	}
	else if (dt->pids[dt->i] == 0)
		deal_with_chp(dt, cmd, pth, env);
	else
		deal_with_pp(dt, cmd);
}

void	deal_with_chp(t_data *dt, t_sh *cmd, char *pth, t_env *env)
{
	if (dt->i > 0)
	{
		dup2(dt->save, 0);
		close(dt->save);
	}
	if (cmd->next)
	{
		close(dt->fd[0]);
		dup2(dt->fd[1], 1);
		close(dt->fd[1]);
	}
	else
	{
		dup2(dt->std_out, 1);
		close(dt->std_out);
	}
	final_ex(cmd, env, pth);
}

void	deal_with_pp(t_data *dt, t_sh *cmd)
{
	if (dt->i > 0)
		close(dt->save);
	if (cmd->next)
	{
		close(dt->fd[1]);
		dt->save = dt->fd[0];
	}
}
void	final_ex(t_sh *cmd, t_env *env, char *pth)
{
	handle_redirections(cmd->dir);
	if (its_bult(cmd->args[0]) == 11)
	{
		execute_builtin(cmd, env);
		exit(ft_hrb(1, 0));
	}
	else
	{
		if (execve(pth, cmd->args, env_to_arr(env, 0)) == -1)
			ft_putstr_x(cmd->args[0], ": command not found\n", NULL, 2);
		exit(ft_hrb(1, 127));
	}
	ft_signal(1);
}
