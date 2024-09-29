#include "minishell.h"


// void	print_them_all(t_sh *cc)
// {
// 	t_sh *cmd = cc;
// 	while(cmd)
// 	{
// 		int i = 0;
// 		while(cmd->args[i])
// 		{
// 			printf("{%s}\n", cmd->args[i]);
// 			i++;
// 		}
// 		while(cmd->dir)
// 		{
// 			printf("%d : %d\n", cmd->dir->tp, cmd->dir->fd_her);
// 			cmd->dir = cmd->dir->next;
// 		}
// 		cmd = cmd->next;
// 	}
// }

void	init_d(t_data *dt, t_sh *cmd)
{
	dt->cnt = ft_lstsize(cmd);
	dt->save = 0;
	dt->std_in = dup(0);
	dt->std_out = dup(1);
	dt->i = 0;
	dt->pids = malloc(sizeof(int) * dt->cnt + 1);
	if (!dt->pids)
	{
		write(2, "malloc", 7);
		exit(ft_hrb(1, 1));
	}
}

void	ft_start_exec(t_sh **cmd, t_env **env)
{
	t_data	dt;
	char	**pth;
	
	// print_them_all(*cmd);
	pth = environnement_pth(*env);
	init_d(&dt, *cmd);
	if (its_bult((*cmd)->args[0]) == 11 && dt.cnt == 1)
	{
		execute_builtin(*cmd, *env);
		return ;
	}
	while (cmd && *cmd)
	{
		main_exec(&dt, *cmd, *env, pth);
		*cmd = (*cmd)->next;
		dt.i++;
	}
	dt.i = 0;
	while (dt.i < dt.cnt)
	{
		waitpid(dt.pids[dt.i], &dt.status, 0);
		if (WIFEXITED(dt.status))
		{
			// collect exit status
		}
		dt.i++;
	}
	free(dt.pids);
	dup2(dt.std_in, 0);
	close(dt.std_in);
	dup2(dt.std_out, 1);
	close(dt.std_out);
}
