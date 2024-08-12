#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "minishell1.h"
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
void	pars_word(char *input, t_sh **l);
m_sh	*parse_line(char *line, m_sh **cmd);
char	*get_word(char	*str);

// 1 : processing parte
void	pi_processing_err_3(t_sh **l, t_sh **ps, char c0, char c1, char *del);
int		pi_processing_err_1(t_sh **f, t_sh **l, char *del);
void	pi_processing_err_4(t_sh *f, int i, char *del);
void	pi_processing_err_5(t_sh **lst, char *del);
void	pi_processing_err_2(t_sh **f, char *del);
t_sh	*pi_processing_cmd(t_sh **lst, char *del);

/*############      list      ############ */
void	ft_lstadd_front(t_sh **lst, t_sh *new);
void	ft_lstadd_back_tsh(t_sh **lst, t_sh *new);
t_sh	*ft_lstnew(char *content);
t_sh	*ft_lstlast(t_sh **lst);
int		ft_lstsize(t_sh *lst);


/*############ pars command ##############*/
t_sh	*parse_commands_2(t_sh **n, char const *string);
t_sh	*parse_commands_1(char const *string);
t_sh	*create_commands(char **words);

/*############    checker    ##############*/
int		check_pos_here(t_sh **lst, t_sh **breaking);
int		checker_typing(char const *santax);
int		check_herepipe(t_sh **l);
int		check_op(char c);
int		check_op1(ee i);
void	free_tsh(t_sh **likend);
void	synatx_error(char *str);
void	print_errors();


/*--------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------*/

void	complete_type(t_sh **lst, int type);
char	*ft_strdup(char const *src);
size_t	ft_strlen(const char *theString);
t_redir	*creat_node(char *str, t_redir *node);
m_sh	*creat_commandline(m_sh **node, char *str, int i);

/*#################   string   #####################*/
void	pi_processing_here(int	fd, char *dilemiter);
m_sh	*pi_processing_pro(char *str, m_sh **node);
char	*pi_processing_dir(char *str, m_sh **h_n);
m_sh	*pi_processing_data(char *str);
char	*restory_cmd(char *src);
void	run_heredoc(char *arg, int i);

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
char	*f_strjoin(char *str1, char *str2, int line_b);
int		count_word(char const *string, char c);
char	*get_dilemter(char *inf, int *j);
char	*free_line(char *back_buf);
int		check_nl(char const *str);
char	*start(char *arr, int fd);
char	*get_next_line(int fd);
char	*by_line(char *str);
char	*f_insial(void);


#endif