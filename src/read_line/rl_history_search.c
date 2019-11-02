#include "msh.h"

int		rl_history_search(long ch)
{
	char 	*line;

	if (ch != CTRL_R)
		return (EXIT_FAILURE);
	line = g_msh->rl->line;
	ft_printf("Hello, im search function\n");
	return (EXIT_SUCCESS);
}
