#include "../prs/minishell.h"

void handle_redirections(t_redir *redirections)
{
	t_redir *redir = redirections;
	int	fd;
	while (redir)
	{
		if (redir->tp == 3)// output 
		{
			fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fd < 0)
			{
				perror("open");
				exit(1);
			}
			dup2(fd, 1);
			close(fd);
		}
		else if (redir->tp == 5)//append
		{
			fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (fd < 0)
			{
				perror("open");
				exit(1);
			}
			dup2(fd, 1);
			close(fd);
		}
		else if (redir->tp == 2)//input
		{
			fd = open(redir->file_name, O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				exit(1);
			}
			dup2(fd, 0);
			close(fd);
		}
		redir = redir->next;
	}
}
