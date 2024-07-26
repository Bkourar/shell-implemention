#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


typedef enum	type{word, Pipe, input, output, heredoc,
append, d_quot, s_quot, dolar, err} ee;

typedef struct command_line
{
	char				*token;
	char				*stat;
	ee					type;
	struct command_line	*nx;
	struct command_line *pv;
}						t_sh;

/*############      parsing      ############ */
char	**ft_split(char const *s, char c);
void	pars_word(char *input, t_sh **l);
void	*parse_line(char *line);
// 1 : processing parte
void	pi_processing_err_3(t_sh **l, t_sh **ps, char c0, char c1);
void	pi_processing_err_1(t_sh **f, t_sh **l);
void	pi_processing_err_4(t_sh *f, int i);
void	pi_processing_err_5(t_sh **lst);
void	pi_processing_err_2(t_sh **f);
t_sh	*pi_processing_cmd(t_sh **lst);

/*############      list      ############ */
void	ft_lstadd_front(t_sh **lst, t_sh *new);
void	ft_lstadd_back(t_sh **lst, t_sh *new);
t_sh	*ft_lstnew(char *content);
t_sh	*ft_lstlast(t_sh **lst);
t_sh	*ft_shell_last(t_sh **lst);
int		ft_lstsize(t_sh *lst);

/*############ pars command ##############*/
t_sh	*parse_commands_2(t_sh **n, char const *string);
t_sh	*parse_commands_1(char const *string);
t_sh	*create_commands(char **words);

/*############    checker    ##############*/
int		check_pos_here(t_sh **lst, t_sh **breaking);
int		check_herepipe(t_sh **l);
int		check_op(char c);
int		check_op1(ee i);
void	free_linked(t_sh **likend);
void	synatx_error(char *str);
void	print_errors();



#endif