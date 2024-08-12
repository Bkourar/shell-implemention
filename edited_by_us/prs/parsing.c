#include "minishell.h"

int	pi_processing_err_1(t_sh **f, t_sh **l, char *del)
{
	t_sh	*t;

	if ((*f)->type == Pipe || ((*f)->nx == NULL && check_op1((*f)->type)))
		return (synatx_error((*f)->token), 1);
	else if ((*l)->type == Pipe && !check_herepipe(f))
		return (run_heredoc(del, 0), synatx_error((*l)->token), 1);//here run herdoc && errors
	else if ((*l)->type == Pipe && check_herepipe(f) != 0)
		return (synatx_error((*l)->token), 1);//here run just 
	else if (check_op1((*l)->type) && !check_op1((*l)->pv->type)
		&& !check_herepipe(f))
		return (run_heredoc(del, 0), print_errors(), 1);//here run herdoc && error
	else if (check_op1((*l)->type) && !check_op1((*l)->pv->type) 
		&& check_herepipe(f) != 0)
		return (print_errors(), 1);// here run just error
	t = (*f);
	while (t->nx != NULL)
	{
		if (t->type == Pipe && t->nx->type == Pipe && !check_pos_here(f, &t->nx))
			return (synatx_error("|"), 1);//here run just err
		else if (t->type == Pipe && t->nx->type == Pipe && check_pos_here(f, &t->nx))
			return (run_heredoc(del, 0), synatx_error("|"), 1);//here run heredoc && run err
		t = t->nx;
	}
	return (0);
}

int	pi_processing_err_2(t_sh **f, char *del)
{
	t_sh	*tp;
	t_sh	*tp1;

	tp = (*f);
	tp1 = (*f)->nx;
	while (tp1 != NULL)
	{
		if (check_op1(tp->type) && check_op1(tp1->type))
		{
			if (!check_pos_here(f, &tp1))
				return (synatx_error(tp1->token), 1);//here run just err
			else
				return (run_heredoc(del, 0), synatx_error(tp1->token), 1);//here run heredoc && err
		}
		else if (check_op1(tp->type) && tp1->type == Pipe)
		{
			if (!check_pos_here(f, &tp1))
				return (synatx_error(tp1->token), 1);//here run just err
			else
				return (run_heredoc(del, 0), synatx_error(tp1->token), 1);//here run heredoc && err
		}
		tp = tp1;
		tp1 = tp1->nx;
	}
	return (0);
}

int	pi_processing_err_4(t_sh *f, int i, char *del)
{
	while (f)
	{
		i = 0;
		if (f != NULL && f->type == s_quot)
		{
			while (f != NULL && i != 2)
			{
				if (f->type == s_quot) i++;
				f = f->nx;
			}
		}
		if (f != NULL && f->type == d_quot)
		{
			while (f != NULL && i != 2)
			{
				if (f->type == d_quot) i++;
				f = f->nx;
			}
		}
		if (!(i == 2 || i == 0) && f == NULL)
			return (synatx_error("quote"), 1);
		f = f->nx;
	}
	return (0);
}

	// if (i == 2 && f != NULL)
	// 	(pi_processing_err_4(f, 0, del));
	// else if (i == 0 && f != NULL)
	// 	(pi_processing_err_4(f->nx, 0, del));
	// if (f == NULL)
	// 	return ;
int	pi_processing_err_5(t_sh **lst, char *del)
{
	t_sh	*tmp;

	tmp = (*lst);
	while (tmp != NULL)
	{
		if (!strcmp(tmp->token, "echo"))
		{
			tmp = tmp->nx;
			if (tmp == NULL)
				return ;
			else if (tmp->type == s_quot || tmp->type == d_quot)
			{
				if (pi_processing_err_4(tmp, 0, del) == 1)
					return (1);
			}
		}
		tmp = tmp->nx;
	}
	return (0);
}

void	pi_processing_err_3(t_sh **l, t_sh **ps, char c0, char c1, char *del)
{
	if (c1 == '>' && !check_pos_here(l, ps))
		return (synatx_error(">"), 1);//run just err
	else if (c1 == '<' && !check_pos_here(l, ps))
		return (synatx_error("<"), 1);//run just err
	else if (c1 == '>' && check_pos_here(l, ps))
		return (run_heredoc(del, 0), synatx_error(">"), 1);//run here_doc && err
	else if (c1 == '<' && check_pos_here(l, ps))
		return (run_heredoc(del, 0), synatx_error("<"), 1);//run here_doc && err
	else if (c0 == '|' && c1 == '>' && !check_pos_here(l, ps))
		return (synatx_error(">"), 1);//run just err
	else if (c0 == '|' && c1 == '<' && !check_pos_here(l, ps))
		return (synatx_error("<"), 1);//run just err
	else if (c0 == '|' && c1 == '>' && check_pos_here(l, ps))
		return (run_heredoc(del, 0), synatx_error(">"), 1);//run heredoc &&  err
	else if (c0 == '|' && c1 == '<' && check_pos_here(l, ps))
		return (run_heredoc(del, 0), synatx_error("<"), 1);//run heredoc &&  err
	else if (c1 == '|' && !check_pos_here(l, ps))
		return (synatx_error("|"), 1);//run just err
	else if (c1 == '|' && check_pos_here(l, ps))
		return (run_heredoc(del, 0), synatx_error("|"), 1);//run here_doc && err
	return (0);
}

