#ifndef EXPAND_H
# define EXPAND_H

# include "../prs/minishell.h"

# define bool _Bool
# define true 1
# define false 0

typedef enum type_expand
{
	exp,
	not_exp
}	t_type;

typedef enum state_join
{
	init,
	join,
	not_join
}	t_state;

typedef struct s_expand
{
	char			*input;
	t_type			type;
	t_state			state;
	bool			logic;
	struct s_expand	*next;
	struct s_expand	*prv;
}					t_exp;

char	**pi_processing_expand(char *str, t_env **env, bool b);
t_exp	*update_input(char *in, t_exp **lst, bool b);
t_exp	*upgrade_input(char *in, bool b, t_type l, t_state st);
// void	copy_input(char	*dst, char *src, int *i, t_state *st);
void	ft_lstadd_back_texp(t_exp **lst, t_exp *new);
void	upgrade_type(t_type *tp, bool logic);
int		valid_expand(char c);
void	search_and_replace(t_exp **lst, t_env **env, int b);
char	*join_expand(t_exp **lst);
int		valid_condtion(char *str, int p);
// char	**parssing_expand(t_exp **head);
int		check_space(char *str);
int		ft_lstsiz_exp(t_exp *lst);
int		valid_join(char *src, int *i, t_exp *lst);
int		white_sp(char c);
t_exp	*ft_lstlast_exp(t_exp **lst);

#endif