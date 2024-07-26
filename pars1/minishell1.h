#ifndef MINISHELL1_H
# define MINISHELL1_H

typedef enum    type{
    output,
    append,
    input,
    heredoc
} t_e;

typedef struct s_redir
{
	t_e				type;
	char			*file_name;
	int				fd_her;
	char			*delimiter;// used for here-doc
	struct s_redir	*next;
}					t_redir;


typedef struct s_shell
{
	char			**args;// Command and arguments
	t_redir			*red;// Redirections
	struct s_shell	*next;
}					m_sh;

void	pi_processing_arg(char *arg);

#endif