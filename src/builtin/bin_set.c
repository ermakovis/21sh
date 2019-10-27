#include "msh.h"

int		bin_set(t_list *list)
{
	(void)list;
	ft_lstiter(g_msh->env, &print_var);
	ft_lstiter(g_msh->var, &print_var);
	if (!g_msh->env && !g_msh->var)
		return (BIN_FAILURE);
	return (BIN_SUCCESS);
}
