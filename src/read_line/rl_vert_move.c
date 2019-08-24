#include "msh.h"

static void		rl_vm_up(int term_width)
{
	int		moves;

	moves = term_width;
	while (moves--)
		rl_move_cur(LEFT);
}

static void		rl_vm_down(int term_width)
{
	int		moves;

	moves = term_width;
	while (moves--)
		rl_move_cur(RIGHT);
}

void		rl_vert_move(long ch)
{
	int		term_width;
	t_wsize	wsize;

	if (!(ch == UPLINE || ch == DOWNLINE))
		return ;
	ioctl(0, TIOCGWINSZ, &wsize);
	term_width = wsize.ws_col;
	if (ch == UPLINE)
		rl_vm_up(term_width);
	else if (ch == DOWNLINE)
		rl_vm_down(term_width);
}

