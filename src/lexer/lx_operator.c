#include "msh.h"
#include "lexer.h"

int				lx_operator_check(char ch)
{
	if (ch == ';' || ch == '|' || ch == '&')
		return (1);
	return (0);
}

int				lx_operator_get(char *line)
{
	if (ft_strncmp(line, ";", 1) == 0)
		return (add_token(";", OPERATOR, SEMI));
	else if (ft_strncmp(line, "&&", 2) == 0)
		return (add_token("&&", OPERATOR, AND_IF));
	else if (ft_strncmp(line, "&", 1) == 0)
		return (add_token("&", OPERATOR, AND));
	else if (ft_strncmp(line, "||", 2) == 0)
		return (add_token("||", OPERATOR, OR_IF));
	else if (ft_strncmp(line, "|", 1) == 0)
		return (add_token("|", OPERATOR, PIPE));
	return (0);
}
