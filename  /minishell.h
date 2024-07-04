#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_sh
{
	char		*value;
	struct s_sh	*next;
}		t_sh;


/*############      parsing      ############ */
int		ft_strlen(char *s);
t_sh	*ft_pars_it(char *str);

/*############      list      ############ */
t_sh	*ft_lstnew(char *content);
void	ft_lstadd_back(t_sh **lst, t_sh *new);
void	ft_lstadd_front(t_sh **lst, t_sh *new);
int		ft_lstsize(t_sh *lst);
t_sh	*ft_lstlast(t_sh **lst);


#endif