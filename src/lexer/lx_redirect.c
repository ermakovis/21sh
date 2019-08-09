#include "msh.h"
#include "lexer.h"

int				lx_redirect_check(char ch)
{
	if (ch == ';' || ch == '|' || ch == '&' || ch == '<' || ch == '>')
		return (1);
	return (0);
}

int				lx_redirect_get(char *line)
{
	if (ft_strncmp(line, "<<", 2) == 0)
		return (add_token("<<", REDIRECT, DLESS));
	else if (ft_strncmp(line, "<&", 2) == 0)
		return (add_token("<&", REDIRECT, LESS_AND));
	else if (ft_strncmp(line, "<", 1) == 0)
		return (add_token("<", REDIRECT, LESS));
	else if (ft_strncmp(line, ">>", 2) == 0)
		return (add_token(">>", REDIRECT, DMORE));
	else if (ft_strncmp(line, ">&", 2) == 0)
		return (add_token(">&", REDIRECT, MORE_AND));
	else if (ft_strncmp(line, ">", 1) == 0)
		return (add_token(">", REDIRECT, MORE));
	return (0);
}
