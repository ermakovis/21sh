#include "msh.h"

int		rl_history_search(long c)
{
	char 	*line;
	long	ch;

	if (c != CTRL_R)
		return (EXIT_FAILURE);
	ft_printf("Inside>\n");
	while (get_char(&ch))
	{
		if (ch == 4 )
			break ;
		if (ft_isprint(ch))
			ft_printf("%c", ch);
	}
	return (EXIT_SUCCESS);
}
