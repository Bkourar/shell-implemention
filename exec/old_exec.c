#include "../prs/minishell.h"


void	ft_start_exec(m_sh **cmd, t_env **env)
{
	int	fd[2];
	int	input_fd = 0;
	int	std_in = dup(0);
	int	std_out = dup(1);
	int	*pids;
	int	i = 0;
	int	count = ft_lstsize(*cmd);
	int	status;
	char **arr = env_to_arr(*env);
	char **env_arr = environnement_pth(*env);
	char *pth;

	if (its_bult((*cmd)->args[0]) == 11 && count == 1)
	{
		execute_builtin(*cmd, *env);
		return;
	}
	pids = malloc(sizeof(int) * count);
	if (!pids)
	{
		write(2, "malloc", 7);
		exit(1);
	}
	while (cmd && *cmd)
	{
		pth = get_path(env_arr, (*cmd)->args[0]);
		if ((*cmd)->next && pipe(fd) == -1)
		{
			write(2, "pipe", 5);
			exit(1);
		}

		pids[i] = fork();
		if (pids[i] < 0)
		{
			write(2, "fork", 5);
			exit(1);
		}
		else if (pids[i] == 0)
		{ // Child process
			if (i > 0) // I am not in the first command 
			{
				dup2(input_fd, 0); // Redirect input from previous pipe
				close(input_fd);
			}
			if ((*cmd)->next) // I am not the last command
			{
				close(fd[0]); // Close read end of pipe
				dup2(fd[1], 1); // Redirect output to pipe
				close(fd[1]);
			}
			else
			{
				dup2(std_out, 1); // Redirect output to original stdout
				close(std_out);
			}
			if (its_bult((*cmd)->args[0]) == 11)
			{
				handle_redirections((*cmd)->dir); // Handle redirections
				execute_builtin(*cmd, *env); // Execute built-in command
				exit(0);
			}
			else
			{
				handle_redirections((*cmd)->dir); // Handle redirections
				if (execve(pth, (*cmd)->args, arr) == -1)
				{
					printf("bash: %s: command not found\n", (*cmd)->args[0]);
				}
				exit(1);
			}
		}
		else
		{ // ppparent process
			if (i > 0)
				close(input_fd); // Close previous read end of pipe
			if ((*cmd)->next)
			{
				close(fd[1]); // Close write end of pipe
				input_fd = fd[0]; // save read end of pipe for next command
			}
		}
		*cmd = (*cmd)->next;
		i++;
	}
	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0); // Wait for each child process
		if (WIFEXITED(status))
		{
			// Collect exit status
		}
		i++;
	}
	free(pids);
	dup2(std_in, 0); // Restore original stdin
	close(std_in);
	dup2(std_out, 1); // Restore original stdout
	close(std_out);
}
/*
!!!!!!!!!! warning !!!!!!!!!!
		do not touch 		
		danger zone 		
*/


/*

// void init_data(t_data *data, int count)
// {
// 	data->input_fd = 0;
// 	data->std_in = dup(0);
// 	data->std_out = dup(1);
// 	data->count = count;
// 	data->i = 0;
// 	data->pids = malloc(sizeof(int) * count);
// 	if (!data->pids)
// 	{
// 		write(2, "malloc", 7);
// 		exit(1);
// 	}
// }

// void handle_child_process(t_data *data, m_sh **cmd, char *pth, t_env *env)
// {
// 	if (data->i > 0)
// 	{
// 		dup2(data->input_fd, 0);
// 		close(data->input_fd);
// 	}
// 	if ((*cmd)->next)
// 	{
// 		close(data->fd[0]);
// 		dup2(data->fd[1], 1);
// 		close(data->fd[1]);
// 	}
// 	else
// 	{
// 		dup2(data->std_out, 1);
// 		close(data->std_out);
// 	}
// 	if (its_bult((*cmd)->args[0]) == 11)
// 	{
// 		handle_redirections((*cmd)->dir);
// 		execute_builtin(*cmd, &env);
// 		exit(0);
// 	}
// 	else
// 	{
// 		handle_redirections((*cmd)->dir);
// 		if (execve(pth, (*cmd)->args, env_to_arr(env)) == -1)
// 			printf("command not found\n");
// 		exit(EXIT_FAILURE);
// 	}
// }

// void handle_parent_process(t_data *data, m_sh **cmd)
// {
// 	if (data->i > 0)
// 		close(data->input_fd);

// 	if ((*cmd)->next)
// 	{
// 		close(data->fd[1]);
// 		data->input_fd = data->fd[0];
// 	}
// }

// void wait_for_children(t_data *data)
// {
// 	int	i;
// 	i = 0;
// 	while (i < data->count)
// 	{
// 		waitpid(data->pids[i], &data->status, 0);
// 		if (WIFEXITED(data->status))
// 		{
// 			// Collect exit status if needed
// 		}
// 		i++;
// 	}
// 	free(data->pids);
// }



// void handle_piping_and_forking(t_data *data, m_sh **cmd, t_env **env)
// {
// 	char	*pth;

// 	pth = get_path(environnement_pth(*env), (*cmd)->args[0]);
// 	if ((*cmd)->next && pipe(data->fd) == -1)
// 	{
// 		write(2, "pipe", 5);
// 		exit(1);
// 	}

// 	data->pids[data->i] = fork();
// 	if (data->pids[data->i] < 0)
// 	{
// 		write(2, "fork", 5);
// 		exit(1);
// 	}
// 	else if (data->pids[data->i] == 0)
// 	{
// 		handle_child_process(data, cmd, pth, *env);
// 	}
// 	else
// 	{
// 		handle_parent_process(data, cmd);
// 	}
// }

// void ft_start_exec(m_sh **cmd, t_env **env)
// {
// 	t_data	data;

// 	init_data(&data, ft_lstsize(*cmd));

// 	if (its_bult((*cmd)->args[0]) == 11 && data.count == 1)
// 	{
// 		execute_builtin(*cmd, &*env);
// 		return;
// 	}
// 	while (cmd && *cmd)
// 	{
// 		handle_piping_and_forking(&data, cmd, env);
// 		*cmd = (*cmd)->next;
// 		data.i++;
// 	}

// 	wait_for_children(&data);

// 	dup2(data.std_in, 0);
// 	close(data.std_in);
// 	dup2(data.std_out, 1);
// 	close(data.std_out);
// }

*/