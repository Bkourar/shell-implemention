#include "minishell.h"

void	pi_processing_err_1(t_sh **f, t_sh **l)
{
	t_sh	*t;

	if ((*f)->type == Pipe || ((*f)->nx == NULL && check_op1((*f)->type)))
		synatx_error((*f)->token);
	else if ((*l)->type == Pipe && !check_herepipe(f))
		(synatx_error((*l)->token));//here run herdoc && errors
	else if ((*l)->type == Pipe && check_herepipe(f) != 0)
		(synatx_error((*l)->token));//here run just 
	else if (check_op1((*l)->type) && !check_op1((*l)->pv->type)
		&& !check_herepipe(f))
		(print_errors());//here run herdoc && error
	else if (check_op1((*l)->type) && !check_op1((*l)->pv->type) 
		&& check_herepipe(f) != 0)
		print_errors();// here run just error
	t = (*f);
	while (t->nx != NULL)
	{
		if (t->type == Pipe && t->nx->type == Pipe && !check_pos_here(f, &t->nx))
			synatx_error("|");//here run just err
		else if (t->type == Pipe && t->nx->type == Pipe && check_pos_here(f, &t->nx))
			synatx_error("|");//here run heredoc && run err
		t = t->nx;
	}
}

void	pi_processing_err_2(t_sh **f)
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
				(synatx_error(tp1->token));//here run just err
			else
				(synatx_error(tp1->token));//here run heredoc && err
		}
		else if (check_op1(tp->type) && tp1->type == Pipe)
		{
			if (!check_pos_here(f, &tp1))
				(synatx_error(tp1->token));//here run just err
			else
				(synatx_error(tp1->token));//here run heredoc && err
		}
		tp = tp1;
		tp1 = tp1->nx;
	}
}

void	pi_processing_err_4(t_sh *f, int i)
{
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
		(synatx_error("quote"));
	if (i == 2 && f != NULL)
		(pi_processing_err_4(f, 0));
	else if (i == 0 && f != NULL)
		(pi_processing_err_4(f->nx, 0));
	if (f == NULL)
		return ;
}

void	pi_processing_err_5(t_sh **lst)
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
					pi_processing_err_4(tmp, 0);
		}
		tmp = tmp->nx;
	}
}

void	pi_processing_err_3(t_sh **l, t_sh **ps, char c0, char c1)
{
	if (c1 == '>' && !check_pos_here(l, ps))
		(synatx_error(">"));//run just err
	else if (c1 == '<' && !check_pos_here(l, ps))
		(synatx_error("<"));//run just err
	else if (c1 == '>' && check_pos_here(l, ps))
		(synatx_error(">"));//run here_doc && err
	else if (c1 == '<' && check_pos_here(l, ps))
		(synatx_error("<"));//run here_doc && err
	else if (c0 == '|' && c1 == '>' && !check_pos_here(l, ps))
		(synatx_error(">"));//run just err
	else if (c0 == '|' && c1 == '<' && !check_pos_here(l, ps))
		(synatx_error("<"));//run just err
	else if (c0 == '|' && c1 == '>' && check_pos_here(l, ps))
		(synatx_error(">"));//run heredoc &&  err
	else if (c0 == '|' && c1 == '<' && check_pos_here(l, ps))
		(synatx_error("<"));//run heredoc &&  err
	else if (c1 == '|' && !check_pos_here(l, ps))
		(synatx_error("|"));//run just err
	else if (c1 == '|' && check_pos_here(l, ps))
		(synatx_error("|"));//run here_doc && err
	
}

t_sh	*pi_processing_cmd(t_sh **lst)
{
	t_sh	*tmp;

	tmp = (*lst);
	while (tmp != NULL)
	{
		if (tmp->type == err)
			pi_processing_err_3(lst, &tmp, tmp->token[0], tmp->token[1]);
		tmp = tmp->nx;
	}
	tmp = ft_lstlast(lst);
	pi_processing_err_1(lst, &tmp);//pipe
	pi_processing_err_2(lst);//direction
	pi_processing_err_4((*lst), 0);//quote
	pi_processing_err_5(lst);//echo
	return (tmp);
}
