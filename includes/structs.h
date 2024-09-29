#ifndef STRUCTS_H
# define STRUCTS_H

/***********  env  *************/

typedef struct s_env
{
	char	*var;
	char	*value;
	struct s_env	*next;

}			t_env;

/********* data for exuction ******/

typedef enum    tp{
	intial,
	out,
	app,
	in,
	her_doc
}	t_e;

typedef struct s_redir
{
	t_e				tp;
	char			*file_name;
	int				fd_her;
	struct s_redir	*next;
}					t_redir;

typedef struct s_shell
{
	char			**args;
	t_redir			*dir;
	t_env			*env;
	struct s_shell	*next;
}					t_sh;

/********* data for parssing ******/

typedef enum	type{word, Pipe, input, output, heredoc,
append, d_quot, s_quot, dolar, err, L_err} ee;

typedef struct command_line
{
	char				*token;
	char				*stat;
	ee					type;
	t_env				*env;
	struct command_line	*nx;
	struct command_line *pv;
}						t_tk;


/*----------------------------------------------------------------------------------------------------*/

/***********  exec_data  *************/

typedef struct s_data
{
	int fd[2];        // Pipe file descriptors
	int input_fd;     // File descriptor for input, initially set to stdin
	int std_in;       // Saved original stdin file descriptor
	int std_out;      // Saved original stdout file descriptor
	int *pids;
	int count;
	int i;
	int status;
	// char **arr;
	// char **env_arr;
} t_data;

#endif