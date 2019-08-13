#include "msh.h"

int			lx_assignment_check(char *line)
{
	int		len;
	int		eq_pos;
	
	len = 0;	
	if (g_msh->tokens &&\
		((t_token*)g_msh->tokens->content)->token_type != ASSIGNMENT)
		return (0);
	while (line[len] && ft_isprint(line[len]) && !ft_isspace(line[len]))
		len++;
	eq_pos = ft_strclen(line, "=");
	if (eq_pos && len >= eq_pos)
		return (1);
	return (0);
}

int			lx_assignment_get(char *line)
{
	int		len;
	
	len = 0;
	while (line[len] && ft_isprint(line[len]) && !ft_isspace(line[len]))
		len++;
	add_token(line, len, ASSIGNMENT, NONE);	
}
