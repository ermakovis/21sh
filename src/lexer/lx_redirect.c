#include "msh.h"
#include "lexer.h"

int				lx_redirect_check(char ch)
{
	if (ch == '<' || ch == '>')
		return (1);
	return (0);
}

int				lx_redirect_get(char *line)
{
	int		len;

	len = 0;
	while (ft_isdigit(line[len]))
		len++;
	if (ft_strncmp(&line[len], "<<", 2) == 0)
		return (add_token(line, len + 2, REDIRECT, DLESS));
	else if (ft_strncmp(&line[len], "<&", 2) == 0)
		return (add_token(line, len + 2, REDIRECT, LESS_AND));
	else if (ft_strncmp(&line[len], "<", 1) == 0)
		return (add_token(line, len + 1, REDIRECT, LESS));
	else if (ft_strncmp(&line[len], ">>", 2) == 0)
		return (add_token(line, len + 2, REDIRECT, DMORE));
	else if (ft_strncmp(&line[len], ">&", 2) == 0)
		return (add_token(line, len + 2, REDIRECT, MORE_AND));
	else if (ft_strncmp(&line[len], ">", 1) == 0)
		return (add_token(line, len + 1, REDIRECT, MORE));
	return (add_token(line, len, WORD, NONE));
}
