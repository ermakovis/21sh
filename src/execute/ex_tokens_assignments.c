#include "msh.h"

void		ex_tokens_assignments(t_list **list)
{
	t_token		*token;
	char		*line;
	int			eq_pos;

	token = (*list)->content;
	line = token->line;
	eq_pos = ft_strclen(line, "=") - 1;
	line[eq_pos] = 0;
	add_var(line, line + eq_pos + 1, &g_msh->var);
	(*list) = (*list)->next;
}
