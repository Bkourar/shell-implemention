
#include "minishell.h"

t_sh *ft_pars_it(char *str)
{
	t_sh *h;
	int	i;
	int	j;
	int	len;
	char *tmp;

	i = 0;
	h = NULL;
	while(str[i])
	{
		j = 0;
		len = 0;
		while(str[i + len] != '|' && str[i + len])
			len++;
		tmp = malloc(len + 1);
		while(str[i] != '|' && str[i])
			tmp[j++] = str[i++];
		tmp[j] = '\0';
		ft_lstadd_back(&h, ft_lstnew(tmp));
		if(str[i] == '|')
		{
			ft_lstadd_back(&h, ft_lstnew("|"));
			i++;
		}
	}
	return (h);
}
