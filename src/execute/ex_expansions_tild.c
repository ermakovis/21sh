#include "msh.h"

void		ex_expansions_tild(t_token *token)
{
	char	*new;

	if (token->line[0] != '~')
		return ;
	if (!(new = ft_strnew(NAME_MAX)))
		cleanup(-1, "Malloc failed at ex_expansions_tild");
	if (ft_strequ(token->line, "~+"))
		append_line(&new, find_var(g_msh->env, "PWD"), NAME_MAX);
	else if (ft_strequ(token->line, "~-"))
		append_line(&new, find_var(g_msh->env, "OLDPWD"), NAME_MAX);
	else if (ft_strequ(token->line, "~"))
		append_line(&new, find_var(g_msh->env, "HOME"), NAME_MAX);
	else
	{
		ft_memdel((void**)&new);
		return ;
	}
	ft_memdel((void**)&token->line);
	token->line = new;
}
