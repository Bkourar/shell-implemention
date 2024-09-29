#include "minishell.h"

void	cd_home(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->var, "PWD", 4) == 0)
		{
			chdir("/Users/abkacimi");
			ft_set_it(env, "PWD", "/Users/abkacimi");
		}
		env = env->next;
	}
}

void	change_cwd(char *c_pth, t_env *env)
{
	char	old_pwd[PATH_MAX];
	char	pwd[PATH_MAX];
	char	cwd[PATH_MAX];

	ft_strlcpy(old_pwd, ft_get_cwd(), PATH_MAX);
	if (getcwd(pwd, PATH_MAX) == NULL && ft_strncmp(c_pth, "..", 3) == 0)
	{
		chdir("/Users/abkacimi");
	}
	else if (chdir(c_pth) == -1)
	{
		printf("cd: %s NO such file or directory\n", c_pth);
	}
	ft_strlcpy(cwd , ft_get_cwd(), PATH_MAX);
	ft_set_it(env, "OLDPWD", old_pwd);
	ft_set_it(env, "PWD", cwd);
}
void	change_directory(t_sh *cmd, t_env *env)
{
	if (!cmd->args[1])
		cd_home(env);
	else
		change_cwd(cmd->args[1], env);
}
