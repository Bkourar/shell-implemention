#ifndef TOKEN_H
# define TOKEN_H

#include "minishell.h"

char	**ft_split(char const *s, char c);
t_sh	*pi_processing_data(char *str, t_env **env , t_sh **head);
char	*pi_processing_dir(char *str, t_sh **h_n, t_env **env);
t_redir	*get_token_dir(char *str, t_redir **lin, t_env **env, int i);
t_redir	*get_token(char *inf, t_redir **l, t_env **env);
t_tk	*parse_commands_2(t_tk **n, char const *string);
t_tk	*parse_commands_1(char const *st, t_env **env);
t_tk	*create_commands(char **words, t_env **env);
t_sh	*pi_processing_pro(char *str, t_sh **node, t_env **env);
void	up_grade(t_tk **n, char *string);
void	up_date(char *str, t_tk **lst, t_env **env);
char	*get_word(char	*str);
void	pars_word(char *input, t_tk **l, t_env **env);

#endif