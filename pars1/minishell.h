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
append, d_quot, s_quot, dolar} ee;

typedef struct command_line
{
	char				*token;
	ee					type;
	char				*stat;
	struct command_line	*next;
	struct command_line *prev;
}						t_sh;

/*############      parsing      ############ */
char	**ft_split(char const *s, char c);
void	pars_word(char *input, t_sh **l);
t_sh	*parse_line(char *line);
// 1 : processing parte
void	pi_processing_err_1(t_sh **f, t_sh **l);
void	pi_processing_err_3(t_sh *f, int i);
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
t_sh	*parse_commands_2(t_sh **list, char const *string);
t_sh	*parse_commands_1(char const *string);
t_sh	*create_commands(char **words);

/*############    checker    ##############*/
int		check_pos_here(t_sh **lst, t_sh **breaking);
int		checker_whit_here(t_sh **vi, ee i, ee j);
int		checker_not_here(t_sh **vi, ee i, ee j);
int		ertor(t_sh **in);
int		check_herepipe(t_sh **l);
int		check_op(char c);
int		check_op1(ee i);
void	free_linked(t_sh **likend);
void	synatx_error(char *str);
void	print_errors();



#endif