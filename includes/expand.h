#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

# define bool _Bool
# define true 1
# define false 0

#  define ambg_1 1// ""
#  define ambg_2 2// "  val"
#  define ambg_3 3// "val  "
#  define ambg_4 4// "  val  "
#  define ambg_5 5// "val1 val2"
#  define valid 6// "val"

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

typedef enum word
{
	wrd,
	not_wrd
}	t_wd;

typedef struct setting
{
	t_type	tp;
	t_space	sp;
	t_state	st;
}			t_set;

typedef struct parameter
{
	t_type	tp;
	t_wd	wd;
	t_state	st;
}			t_par;

typedef struct s_expand
{
	char			*input;
	t_set			*set;
	bool			logic;
	struct s_expand	*next;
	struct s_expand	*prv;
}					t_exp;

typedef struct s_redirect
{
	char				*input;
	t_par				*par;
	int					ambg;
	struct s_redirect	*next;
	struct s_redirect	*prv;
}					t_dir;

char	*join_arg(char **spl);
char	**pi_processing_expand(char *str, t_env **env, bool b);
char	*pi_processing_redirect(char *in, t_env **env);
char	**parse_value(t_exp **hd, t_env **env);
char	*s_and_r(t_exp **lst, t_env **env);
char	**mise_ajour_input(t_dir **lst);
char	**update_array(t_exp **lst);
char	*join_expand(t_exp **lst);
t_exp	*update_input(char *in, t_exp **lst);
t_exp	*upgrade_input(char *in, bool b, int *chmod);
t_exp	*ft_lstlast_exp(t_exp **lst);
int		valid_expand(char c);
int		valid_condtion(char *str, int p);
int		own_exp(int tp, int sp, int st);
int		condition_expand(char *str);
int		ft_lstsiz_exp(t_exp *lst);
int		ft_lstsiz_dir(t_dir *lst);
int		valid_join(t_exp *nd);
int		check_space(char *str);
int		white_sp(char c);
void	premission(int *chmod, int tp, int sp, int st);
void	copy_standard(char *src, int *i, t_exp **lst);
void	copy_input(char *src, int *i, t_exp **lst);
void	ft_lstadd_back_texp(t_exp **lst, t_exp *new);
void	free_exp(t_exp **lst);
void	free_dir(t_dir **lst);
void	skip_wspace(char *str, int *j, t_exp **lst);
void	expand(char *arr, int *i, t_exp **lst);
void	expand_sq(char *arr, int *i, t_exp **lst);
void	parssing_expand(char *src, int *i, t_exp **head);
void	copy_general(char *src, int *i, t_exp **lst);
void	copy_in_sq(char *src, int *i, t_exp **lst);
void	update_list(char **in, t_exp **lst);
void	upgrade_list(char **in, t_dir **lst);
void	copy_single_q(char *src, int *i, t_exp **lst);
void	cin_singl_q(char *src, int *i, t_exp **lst);
void	copy_general(char *src, int *i, t_exp **lst);
void	cin_singlq(char *src, int *i, t_dir **lst);
void	autortion(char **s, t_exp **l, int rwx, bool b);
void	owner_premt(int *chmod, int	tp, int	wd, int	st);
void	ft_lstadd_back_dir(t_dir **lst, t_dir *new);
void	parse_expand_dir(char *src, int *i, t_dir **head);
void	copy_in_sqoute(char *src, int *i, t_dir **lst);
void	expand_wqoute(char *arr, int *i, t_dir **lst);
void	copy_std_norm(char *src, int *i, t_dir **lst);
void	parsse_wesq(char *src, int *i, t_dir **lst);
void	free_arr(char **arg);
t_dir	*analyse_input(char *in, t_dir **lst);
t_dir	*upgrade_redirect(char *in, int *chmod, int j);
t_dir	*analyse_case_ambg(t_dir *tp, t_env **ev);
t_dir	*check_ambiguous_redirect(t_dir **l);
char	*search_in_eva(t_dir *nd, t_env **ev);
void	put_ambeg(char *str);
int		ambiguous_redirect(t_redir **hd);
t_dir	*config_redirect(char *in, int j, t_dir *nd);
int		check_empty(char *str);
void	copy_gen(char *src, int *i, t_dir **lst);
void	cin_singlq(char *src, int *i, t_dir **lst);
void	copy_singleq(char *src, int *i, t_dir **lst);

#endif