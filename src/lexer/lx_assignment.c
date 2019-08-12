#include "msh.h"

int			lx_assignment_check(char *line)
{
	int		len;
	int		eq_pos;
	
	len = 0;	
	if (ft_isspace(line[len]))
		return (0);
	while (line[len] && ft_isprint(line[len]))
		len++;
	eq_pos = ft_strclen(line, "=");
	ft_printf("%d - %d\n", len, eq_pos);
	if (eq_pos && len >= eq_pos)
		return (1);
	return (0);
}

int			lx_assignment_get(char *line)
{
	int		len;
	
	len = 0;
	while (line[len] && ft_isprint(line[len]))
		len++;
	add_token(line, len, ASSIGNMENT, NONE);	
}
