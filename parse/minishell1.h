#ifndef MINISHELL1_H
# define MINISHELL1_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

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
	struct s_shell	*next;
}					m_sh;

/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/

typedef enum	type{word, Pipe, input, output, heredoc,
append, d_quot, s_quot, dolar, err, L_err} ee;

typedef struct command_line
{
	char				*token;
	char				*stat;
	ee					type;
	struct command_line	*nx;
	struct command_line *pv;
}						t_sh;























// /*#################   checker   ###################*/
// int		_check_op(t_e i);
// int		check__(char c);

// /*#################   get_funtion   ###################*/
// void	get_redir(char *str, char *tp, m_sh **l, int *k);
// char	*get_arg(char *arg, m_sh **lst, int *k);
// char	*get_quote(char *str, char c);
// char	*get_envariable(char *va, m_sh **lst, int *k);

#endif