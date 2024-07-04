#include "minishell.h"

int main ()
{
	t_sh *h = NULL;
	char *input = NULL;
	while(1)
	{
		input = readline("> ");
		h = ft_pars_it(input);
		while(h)
		{
			printf("%s\n", h->value);
			h = h->next;
		}
	}
}