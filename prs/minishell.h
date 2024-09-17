#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "minishell1.h"
# include "../expand/expand.h"
# include <sys/types.h> 
# include <sys/wait.h>
# include <limits.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

/*############      parsing      ############ */
char	**ft_split(char const *s, char c);
void	pars_word(char *input, t_sh **l, t_env **env);
m_sh	*parse_line(char *line, m_sh **cmd, t_env **env);
char	*get_word(char	*str);
int		check_dolar(char *str);
char	*get_dolar(char *str);
int		is_alpha(char c);

// 1 : processing parte
int		pi_processing_err_3(t_sh **l, t_sh **ps, char c0, char c1, char *del);
int		pi_processing_err_1(t_sh **f, t_sh **l, char *del);
int		pi_processing_err_4(t_sh **l, int i, char *del);
int		pi_processing_err_5(t_sh **lst, char *del);
int		pi_processing_err_2(t_sh **f, char *del);
t_sh	*pi_processing_cmd(t_sh **lst, char *del);

/*############      list      ############ */
void	ft_lstadd_front(t_sh **lst, t_sh *new);
void	ft_lstadd_back_tsh(t_sh **lst, t_sh *new);
t_sh	*ft_lstnew(char *content);
t_sh	*ft_lstlast(t_sh **lst);
int		ft_lstsize(m_sh *lst);
int	ft_strcmp(char const *s1, char const *s2);

/*############ pars command ##############*/
t_sh	*parse_commands_2(t_sh **n, char const *string);
t_sh	*parse_commands_1(char const *string, t_env **env);
t_sh	*create_commands(char **words, t_env **env);

/*############    checker    ##############*/
int		check_pos_here(t_sh **lst, t_sh **breaking);
int		checker_typing(char const *santax);
int		check_herepipe(t_sh **l);
int		check_heredoc(t_sh **lst);
int		check_op(char c);
int		check_op1(ee i);
void	free_tsh(t_sh **likend);
void	synatx_error(char *str);
void	synatx_quotes(char c);
void	print_errors();
int	    check_redir(char const *str);
char	loop(t_sh **tmp, ee type, int *j);

//expending
void	change_hastag(char *c1, char *c2, int *j, int *i);
int		check_expend(char c1, char c2);
char	*remove_db_quote(char *str);
void	*ft_calloc(size_t nbr, size_t size);
int		is_numeric(char c);
void	change_space(char *c1, char *c2, int *j, int *i);
char	*removed(char *str, char c, int b, t_env **env);
char	*join_whitout_quote(char const *s1, char const *s2);
int		check_quote(char *str);
char	*expanding(char *str, t_env **env);
int		count_wd(char **spliting);
char	*check_sq(char *str);
/*--------------------------------------------------------------------------------------------------------*/

int		is_quote(char c);
void	complete_type(t_sh **lst, int type);
char	*ft_strdup(char const *src);
size_t	ft_strlen(const char *theString);
t_redir	*creat_node(char *str, t_redir *node, t_env **env);
m_sh	*creat_commandline(m_sh **node, char *str, int *i);
int		check_hash(char *str, int *i);
void	change_dbq(char *c1, char *c2, int *j, int *i);
/*#################   string   #####################*/
void	pi_processing_here(int	fd, char *dilemiter, t_env **env);
m_sh	*pi_processing_pro(char *str, m_sh **node, t_env **env);
char	*pi_processing_dir(char *str, m_sh **h_n, t_env **env) ;
m_sh	*pi_processing_data(char *str, t_env **env);
char	*pi_process_expend(char *str, t_env **env);
char	*restory_cmd(char *src);
void	run_heredoc(char *arg, int i, t_sh **l, m_sh **s);
size_t	_ft_strlen(const char *theString);

/*#################   lists   #####################*/
void	allocation(char *src, size_t l, char **dst, int type);
void	ft_lstadd_redir(t_redir **lst, t_redir *new);
void	ft_lstadd_back_msh(m_sh **lst, m_sh *new);
void	free_msh(m_sh **likend);

/*#################   checker   ###################*/
int	check_pipe(char *str, int j, int i);
int	check_dir(char c);
int	check_type(t_e i);
int	isquote(char c);
/*#################   get_funtion   ###############*/
int		replace_space(char *dst, int *i, char *src);
char	*ft_strncpy(char *dst, char *src, int index);
//open file
int		open_here(char *del);
char	*rand_rot13(char *path);
char	*ft_strjoin(char const *s1, char const *s2);

////here_dock
char	*join_path(char const *s1, char const *s2);
int		count_word(char const *string, char c);
char	*get_dilemter(char *inf, int *j);

/*################  exec   ################*/
void	ft_start_exec(m_sh **cmd, t_env **env);
void	execute_builtin(m_sh *cmd, t_env *env);
int		its_bult(char *cmd);
void	handle_redirections(t_redir *redirections);
void	build_echo(char **args, int i);
void	ft_pwd(void);
void	ft_unset(m_sh *cmd, t_env *env);
void	build_export(m_sh *cmd, t_env *env);
void	ft_set_it(t_env *env, const char *var, const char *new_value);
char	*ft_get_cwd();
void	ft_show_env(t_env *env);
void	change_directory(m_sh *cmd,t_env *env);
int		ft_hrb(int flag, int stt);

/*################   env   ################*/
t_env	*parse_env(char **envir);
char	**env_to_arr(t_env *env);
char	**environnement_pth(t_env *e);
char	*get_path(char **arr, char *cmd);
void	ft_del_one(t_env *head, const char *var);
t_env	*env_lstnew(const char *var, const char *value);
void	env_lst_back(t_env **lst, t_env *new);

/*################   more   ################*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*exec_join(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_isalnum(char c);
int		ft_isalpha(char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);


#endif