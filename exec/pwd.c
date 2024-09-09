#include "../prs/minishell.h"

char	*ft_get_cwd()
{
	static char	s_pwd[PATH_MAX];
	char		tmp[PATH_MAX];

	if (getcwd(tmp, PATH_MAX) != NULL)
	{
		ft_strlcpy(s_pwd, tmp, PATH_MAX);
	}
	return (s_pwd);
}

void	ft_pwd(void)
{
	char		cwd[PATH_MAX];
	static char	s_cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		printf("%s\n", cwd);
		ft_get_cwd();
		ft_strlcpy(s_cwd, cwd, PATH_MAX);
	}
	else
		printf("%s\n", s_cwd);
}