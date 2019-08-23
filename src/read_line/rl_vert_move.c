#include "msh.h"

static void		rl_vm_up(int term_width, int prompt_width)
{
	int		moves;
	int		line_len;

	moves = 0;
	line_len = g_msh->rl->line_len;
	if (line_len - term_width > prompt_width)
		moves = term_width;
	else
		moves = term_width - prompt_width;
	while (moves--)
		rl_move_cur(LEFT);
}

static void		rl_vm_down(int term_width, int prompt_width)
{
	int		moves;

	moves = term_width;
	while (moves--)
		rl_move_cur(RIGHT);
}

static int		rl_vm_calc_prompt_len(void)
{
	char	*home;
	char	*pwd;
	int		home_len;
	int		pwd_len;
	int		extra_symbols;

	extra_symbols = 5;
	home = find_var(g_msh->env, "HOME");
	pwd = find_var(g_msh->env, "PWD");
	home_len = ft_strlen(home);
	pwd_len = ft_strlen(pwd);
	if (ft_strnequ(pwd, home, home_len))
		return (pwd_len - home_len + extra_symbols);
	else
		return (pwd_len + extra_symbols);
}

void		rl_vert_move(long ch)
{
	int		term_width;
	int		prompt_width;
	t_wsize	wsize;

	if (!(ch == UPLINE || ch == DOWNLINE))
		return ;
	ioctl(0, TIOCGWINSZ, &wsize);
	term_width = wsize.ws_col;
	prompt_width = rl_vm_calc_prompt_len();
	if (ch == UPLINE)
		rl_vm_up(term_width, prompt_width);
	else if (ch == DOWNLINE)
		rl_vm_down(term_width, prompt_width);
}

