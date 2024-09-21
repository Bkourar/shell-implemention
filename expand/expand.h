#ifndef EXPAND_H
# define EXPAND_H

# include "../prs/minishell.h"

# define bool _Bool
# define true 1
# define false 0

typedef enum expanse
{
	not_exp,
	exp
}	t_type;

typedef enum space
{
	not_skip,
	skip
}	t_space;

typedef enum state
{
	not_join,
	join
}	t_state;

typedef struct setting
{
	t_type	tp;
	t_space	sp;
	t_state	st;
}			t_set;

typedef struct s_expand
{
	char			*input;
	t_set			*set;
	bool			logic;
	struct s_expand	*next;
	struct s_expand	*prv;
}					t_exp;
void	premission(int *chmod, int tp, int sp, int st);
char	**pi_processing_expand(char *str, t_env **env, bool b);
t_exp	*update_input(char *in, t_exp **lst);
t_exp	*upgrade_input(char *in, bool b, int *chmod);
void	copy_input(char *src, int *i, t_exp **lst);
void	copy_standard(char *src, int *i, t_exp **lst);
void	ft_lstadd_back_texp(t_exp **lst, t_exp *new);
int		valid_expand(char c);
char	*s_and_r(t_exp **lst, t_env **env);
char	*join_expand(t_exp **lst);
int		valid_condtion(char *str, int p);
int		valid_join(t_exp *nd);
// char	*expand_whit_dq(char *in, t_exp **lst, t_type *tp);
// char	**parssing_expand(t_exp **head);
int		check_space(char *str);
int		ft_lstsiz_exp(t_exp *lst);
// int		valid_join(char *src, int *i, t_exp *lst);
int		white_sp(char c);
t_exp	*ft_lstlast_exp(t_exp **lst);
int		condition_expand(char *str);
void	free_exp(t_exp **lst);
void	skip_wspace(char *str, int *j, t_exp **lst);
char	**update_array(t_exp **lst);
void	expand(char *arr, int *i, t_exp **lst);
void	expand_sq(char *arr, int *i, t_exp **lst);
void	parssing_expand(char *src, int *i, t_exp **head);
void	copy_general(char *src, int *i, t_exp **lst);
void	copy_in_sq(char *src, int *i, t_exp **lst);
void	update_list(char **in, t_exp **lst);
void	copy_single_q(char *src, int *i, t_exp **lst);
void	cin_singl_q(char *src, int *i, t_exp **lst);
char	**parse_value(t_exp **hd, t_env **env);
int		own_exp(int tp, int sp, int st);
void	free_arr(char **arg);
void	autortion(char **s, t_exp **l, int rwx, bool b);

#endif