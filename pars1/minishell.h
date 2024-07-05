#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct word
{
	char		*token;
	char		*type;
	char		*stat;
	struct word	*next;
}				t_word;

typedef struct command_line
{
	char				*token;
	char				*type;
	char				*stat;
	t_word				*word;
	struct command_line	*next;
}						t_sh;


/*############      parsing      ############ */
char	**ft_split(char const *s, char c);
t_word	*pars_pipe(char const *str);
int		parse_line(char *line);


/*############      list      ############ */
void	ft_lstadd_back(t_word **lst, t_word *new);
void	ft_lstadd_front(t_word **lst, t_word *new);
t_word	*ft_lstnew(char *content);
t_word	*ft_lstlast(t_word **lst);
int		ft_lstsize(t_word *lst);

/*############ pars command ##############*/

void	ft_add_back(t_sh **lst, t_sh *new);
t_sh	*ft_shell_last(t_sh **lst);
t_sh	*create_commands(char **words);
t_sh	*parse_commands_1(char const *string);
t_sh	*parse_commands_2(t_sh **list, char const *string);

/*############ pars word ##############*/
t_word	*parse_word_2(t_word **list, char const *string);
t_word	*pars_word(char const *str);
t_word	*parse_word_1(char const *string);

#endif