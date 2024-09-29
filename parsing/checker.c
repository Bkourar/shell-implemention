#include "minishell.h"

int	check_dir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	check_type(t_e i)
{
	if (i == in || i == out || i == app || i == her_doc)
		return (i);
	return (0);
}

int	isquote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\"')
		return (1);
	if (c == '\'')
		return (2);
	return (0);
}

int check_op(char c)
{
	if (!(c == '<' || c == '>' || c == '$' || c == '|' || c == '\"' || c == '\''))
		return (1);
	return (0);
}

