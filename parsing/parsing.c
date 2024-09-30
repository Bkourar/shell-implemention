#include "minishell.h"

int	pi_processing_err_1(t_tk **f, t_tk **l, char *del)
{
	t_tk	*t;

	if ((*f)->type == Pipe || ((*f)->nx == NULL && check_op1((*f)->type)))
		return (synatx_error((*f)->token), synatx_error("1000000"), 1);
	else if ((*l)->type == Pipe && !check_herepipe(f))
		return (run_heredoc(del, 0, f), synatx_error((*l)->token), synatx_error("3535353"),1);//here run herdoc && errors
	else if ((*l)->type == Pipe && check_herepipe(f) != 0)
		return (synatx_error((*l)->token), synatx_error("9999"), 1);//here run just 
	else if (check_op1((*l)->type) && !check_op1((*l)->pv->type)
		&& !check_herepipe(f))
		return (run_heredoc(del, 0, f), print_errors(), puts("42"), 1);//here run herdoc && error
	else if (check_op1((*l)->type) && !check_op1((*l)->pv->type) 
		&& check_herepipe(f) != 0)
		return (print_errors(), puts("1337"), 1);// here run just error
	t = (*f);
	while (t->nx != NULL)
	{
		if (t->type == Pipe && t->nx->type == Pipe && !check_pos_here(f, &t->nx))
			return (synatx_error("|78787878"), 1);//here run just err
		else if (t->type == Pipe && t->nx->type == Pipe && check_pos_here(f, &t->nx))
			return (run_heredoc(del, 0, f), synatx_error("|21212121"), 1);//here run heredoc && run err
		t = t->nx;
	}
	return (0);
}

int	pi_processing_err_2(t_tk **f, char *del)
{
	t_tk	*tp;
	t_tk	*tp1;

	tp = (*f);
	tp1 = (*f)->nx;
	while (tp1 != NULL)
	{
		if (check_op1(tp->type) && check_op1(tp1->type))
		{
			if (!check_pos_here(f, &tp1))
				return (synatx_error(tp1->token), synatx_error("222"),1);//here run just err
			else
				return (run_heredoc(del, 0, f), synatx_error(tp1->token), synatx_error("3333"),1);//here run heredoc && err
		}
		else if (check_op1(tp->type) && tp1->type == Pipe)
		{
			if (!check_pos_here(f, &tp1))
				return (synatx_error(tp1->token), synatx_error("4444"),1);//here run just err
			else
				return (run_heredoc(del, 0, f), synatx_error(tp1->token), synatx_error("777"),1);//here run heredoc && err
		}
		tp = tp1;
		tp1 = tp1->nx;
	}
	return (0);
}

int	pi_processing_err_4(t_tk **l, int i, char *del)
{
	t_tk	*f;
	char	c;

	f = (*l);
	while (f)
	{
		if (f != NULL && f->type == s_quot)
			c = loop(&f, f->type, &i);
		else if (f != NULL && f->type == d_quot)
			c = loop(&f, f->type, &i);
		if (!(i == 2 || i == 0) && f == NULL && !check_heredoc(l))
			return (synatx_quotes(c), 1);
		else if (!(i == 2 || i == 0) && f == NULL && check_heredoc(l) != 0)
			return (puts("error 102"), synatx_quotes(c), run_heredoc(del, 0, l), 1);
		else if (i == 2 && f != NULL)
			i = 0;
		else if (i == 0 && f != NULL)
		{
			i = 0;
			f = f->nx;
		}
	}
	return (0);
}

int	pi_processing_err_5(t_tk **lst, char *del)
{
	t_tk	*tmp;

	tmp = (*lst);
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->token, "echo"))
		{
			tmp = tmp->nx;
			if (tmp == NULL)
				break ;
			else if (tmp->type == s_quot || tmp->type == d_quot)
			{
				if (pi_processing_err_4(&tmp, 0, del) == 1)
					return (1);
			}
		}
		tmp = tmp->nx;
	}
	return (0);
}

int	pi_processing_err_3(t_tk **l, t_tk **ps, char c0, char c1, char *del)
{
	if (c1 == '>' && !check_pos_here(l, ps))
		return (synatx_error(">1"), 1);//run just err
	else if (c1 == '<' && !check_pos_here(l, ps))
		return (synatx_error("<2"), 1);//run just err
	else if (c1 == '>' && check_pos_here(l, ps))
		return (run_heredoc(del, 0, l), synatx_error(">3"), 1);//run here_doc && err
	else if (c1 == '<' && check_pos_here(l, ps))
		return (run_heredoc(del, 0, l), synatx_error("<4"), 1);//run here_doc && err
	else if (c0 == '|' && c1 == '>' && !check_pos_here(l, ps))
		return (synatx_error(">5"), 1);//run just err
	else if (c0 == '|' && c1 == '<' && !check_pos_here(l, ps))
		return (synatx_error("<6"), 1);//run just err
	else if (c0 == '|' && c1 == '>' && check_pos_here(l, ps))
		return (run_heredoc(del, 0, l), synatx_error(">7"), 1);//run heredoc &&  err
	else if (c0 == '|' && c1 == '<' && check_pos_here(l, ps))
		return (run_heredoc(del, 0, l), synatx_error("<8"), 1);//run heredoc &&  err
	else if (c1 == '|' && !check_pos_here(l, ps))
		return (synatx_error("|9"), 1);//run just err
	else if (c1 == '|' && check_pos_here(l, ps))
		return (run_heredoc(del, 0, l), synatx_error("|10"), 1);//run here_doc && err
	return (0);
}

