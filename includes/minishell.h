#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"
# include "signal.h"
# include "expand.h"
# include "token.h"
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
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

/*############      parsing      ############ */

t_sh	*parse_line(char *line, t_sh **cmd, t_env **env);
int		check_dolar(char *str);
char	*get_dolar(char *str);
int		is_alpha(char c);
char	*check_and_dup(char c);
void    free_shell_list(t_sh *cmds);
// 1 : processing parte
int		pi_processing_err_3(t_tk **l, t_tk **ps, char c0, char c1, char *del);
int		pi_processing_err_1(t_tk **f, t_tk **l, char *del);
int		pi_processing_err_4(t_tk **l, int i, char *del);
int		pi_processing_err_5(t_tk **lst, char *del);
int		pi_processing_err_2(t_tk **f, char *del);
t_tk	*pi_processing_cmd(t_tk **lst, char *del);

/*############      list      ############ */
void	ft_lstadd_front(t_tk **lst, t_tk *new);
void	ft_lstadd_back_tsh(t_tk **lst, t_tk *new);
t_tk	*ft_lstnew(char *content);
t_tk	*ft_lstlast(t_tk **lst);
int		ft_lstsize(t_sh *lst);
int		ft_strcmp(char const *s1, char const *s2);

/*############    checker    ##############*/
int		check_pos_here(t_tk **lst, t_tk **breaking);
int		checker_typing(char const *santax);
int		check_herepipe(t_tk **l);
int		check_heredoc(t_tk **lst);
int		check_op(char c);
int		check_op1(ee i);
void	free_tsh(t_tk **likend);
void	synatx_error(char *str);
void	synatx_quotes(char c);
void	print_errors();
int		check_redir(char const *str);
char	loop(t_tk **tmp, ee type, int *j);
int		check_expend(char c1, char c2);
// void	*ft_calloc(size_t nbr, size_t size);
int		is_numeric(char c);
void	change_space(char *c1, char *c2, int *j, int *i);
char	*join_whitout_quote(char const *s1, char const *s2);
int		check_quote(char *str);
int		count_wd(char **spliting);
char	*dup_quote(char *str, int *i, char c);
/*--------------------------------------------------------------------------------------------------------*/

int		is_quote(char c);
void	complete_type(t_tk **lst, int type);
char	*ft_strdup(char const *src);
size_t	ft_strlen(const char *theString);
t_redir	*creat_node(char *str, t_redir *node, t_env **env);
t_sh	*creat_commandline(t_sh **node, char *str, int *i);
int		check_hash(char *str, int *i);
void	change_dbq(char *c1, char *c2, int *j, int *i);
void	pi_processing_here(int	fd, char *dilemiter, t_env **env, bool *b);
char	*restory_cmd(char *src);
void	run_heredoc(char *arg, int i, t_tk **l);
size_t	_ft_strlen(const char *theString);

/*#################   lists   #####################*/
void	allocation(char *src, size_t l, char **dst, int type);
void	ft_lstadd_redir(t_redir **lst, t_redir *new);
void	ft_lstadd_back_msh(t_sh **lst, t_sh *new);
void	free_msh(t_sh **likend);

/*#################   checker   ###################*/
int		check_pipe(char *str, int j, int i);
int		check_dir(char c);
int		check_type(t_e i);
int		isquote(char c);
/*#################   get_funtion   ###############*/
int		replace_space(char *dst, int *i, char *src);
char	*ft_strncpy(char *dst, char *src, int index);
//open file
int		open_here(char *del, t_env **env, char *c, bool *b);
char	*rand_rot13(char *path);
char	*ft_strjoin(char const *s1, char const *s2);

////here_dock
char	*join_path(char const *s1, char const *s2);
int		count_word(char const *string, char c);
char	*get_dilemter(char *inf, int *j, bool *logic);
void	ft_start_exec(t_sh **cmd, t_env **env);
void	main_exec(t_data *dt, t_sh *cmd, t_env *env, char **path);
void	execute_builtin(t_sh *cmd, t_env *env);
int		its_bult(char *cmd);
void	handle_redirections(t_redir *redirections);
void	build_echo(char **args, int i);
void	ft_pwd(void);
void	ft_unset(t_sh *cmd, t_env *env);
void	ft_exit(t_sh *cmd);
void	build_export(t_sh *cmd, t_env *env);
void	ft_set_it(t_env *env, const char *var, const char *new_value);
char	*ft_get_cwd();
void	ft_show_env(t_env *env);
void	change_directory(t_sh *cmd,t_env *env);
int		ft_hrb(int flag, int stt);

/*################   env   ################*/
t_env		*parse_env(char **envir);
char		**env_to_arr(t_env *env, int i);
char		**environnement_pth(t_env *e);
char		*get_path(char **arr, char *cmd);
void		ft_del_one(t_env *head, const char *var);
t_env		*env_lstnew(const char *var, const char *value);
void		env_lst_back(t_env **lst, t_env *new);


/*################   more   ################*/
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*exec_join(char const *s1, char const *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_isalnum(char c);
int			ft_isalpha(char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_perror(char *str, int st);
void		ft_putstr_x(char *s1,char *s2, char *s3, int fd);
long long	atoll_x(char *str);


#endif