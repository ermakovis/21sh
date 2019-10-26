#include "msh.h"

int		bin_print_error(char *message, char *function_name, char ***tokens)
{
	ft_dprintf(2, "%s: %s: %s\n", g_msh->shell_name, function_name, message);
	if (tokens && *tokens)
		ft_free_table(tokens);
	return (BIN_FAILURE);
}



