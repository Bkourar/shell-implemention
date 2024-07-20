#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_redir
{
	char	*type;
	char	*file_name;
	int		inp_fd;
}			t_redir;

typedef struct s_shell
{
	char			**args;
	t_redir			*red;
	struct s_shell			*next;
}					t_sh;


t_sh	*ft_lstnew(char **args, t_redir *red)
{
	t_sh	*n_node;

	n_node = malloc(sizeof(t_sh));
	if (!n_node)
		return (NULL);
	n_node->args = args;
	n_node->red = red;
	n_node->next = NULL;
	return (n_node);
}

void	ft_lstadd_back(t_sh **lst, t_sh *new)
{
	t_sh	*temp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	print_list(t_sh *lst)
{
	int	i;

	while (lst)
	{
			i = 1;
			printf("Command: %s\n", lst->args[0]);
			while (lst->args[i])
			{
				printf("Arg: %s\n", lst->args[i]);
				i++;
			}
		if (lst->red)
		{
			printf("Redirection Type: %s\n", lst->red->type);
			printf("File Name: %s\n", lst->red->file_name);
			printf("Input FD: %d\n", lst->red->inp_fd);
		}
		lst = lst->next;
		printf("\n");
	}
}

int main()
{
	printf("ls -l | sort -n > file.txt \n\n");
	char *cmd1[] = {"ls", "-l", NULL};
	char *cmd2[] = {"sort", "-n", NULL};

	t_redir redir1 = {NULL, NULL, -1};
	t_sh *node1 = ft_lstnew(cmd1, &redir1);

	// y3ni hna kayna PIPE

	t_redir redir2 = {"out_red >", "file.txt", -1};
	t_sh *node2 = ft_lstnew(cmd2, &redir2);

	t_sh *cmd_lst = NULL;

	ft_lstadd_back(&cmd_lst, node1);
	ft_lstadd_back(&cmd_lst, node2);

	print_list(cmd_lst);
}

