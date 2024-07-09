#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// enum	type{word, pipe, input, output, heredoc,
// append, d_quot, s_quot, dolar};

typedef struct command_line
{
	char				*token;
	char				*type;
	char				*stat;
	struct command_line	*next;
}						t_sh;

/*############      parsing      ############ */
char	**ft_split(char const *s, char c);
int		parse_line(char *line);

/*############      list      ############ */
void	ft_lstadd_back(t_sh **lst, t_sh *new);
void	ft_lstadd_front(t_sh **lst, t_sh *new);
t_sh	*ft_lstnew(char *content);
t_sh	*ft_lstlast(t_sh **lst);
int		ft_lstsize(t_sh *lst);

/*############ pars command ##############*/
t_sh	*ft_shell_last(t_sh **lst);
t_sh	*create_commands(char **words);
t_sh	*parse_commands_1(char const *string);
t_sh	*parse_commands_2(t_sh **list, char const *string);

/*############ pars word ##############*/
void	pars_word(char *input, t_sh **l);

/*############    checker    ##############*/
int check_op(char c);
void	free_linked(t_sh **likend);

#endif