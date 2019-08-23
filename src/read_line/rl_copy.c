#include "msh.h"


void			rl_copy_paste(void)
{
	char 	*line;

	line = g_msh->copy_buffer;
	if (!line)
		return ;
	while (*line)
	{
		rl_print_char(*line);
		line++;
	}
}

void			rl_copy(long ch)
{
	if (!(ch == VMODE || ch == PASTE))
		return ;
	if (ch == VMODE)
		rl_copy_movements();
	else if (ch == PASTE)
		rl_copy_paste();
}
