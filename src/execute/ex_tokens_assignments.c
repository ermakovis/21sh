#include "msh.h"

void		ex_tokens_assignments(t_list **list)
{
	t_token		*token;
	char		*line;
	int			eq_pos;

	if (!*list)
		return ;
	token = (*list)->content;
	if (token->token_type != ASSIGNMENT)
		return ;
	line = token->line;
	eq_pos = ft_strclen(line, "=") - 1;
	line[eq_pos] = 0;
	if (find_var(g_msh->var, line))
		set_var(g_msh->var, line, line + eq_pos + 1);
	else
		add_var(line, line + eq_pos + 1, &g_msh->var);
	ft_lstpop(list, &del_token);
	ex_tokens_assignments(list);
}
