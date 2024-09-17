#include "expand.h"

void	free_exp(t_exp **lst)
{
	t_exp	*tmp;
	if (!lst || !(*lst))
		return ;
	tmp = (*lst)->next;
	while (tmp)
	{
		free((*lst)->input);
		free((*lst));
		(*lst) = tmp;
		tmp = tmp->next;
	}
	free((*lst)->input);
	free((*lst));
	free(lst);
	(*lst) = NULL;
}
