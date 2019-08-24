#include "msh.h"

static int		rl_calc_prompt_len(void)
{
	char	*home;
	char	*pwd;
	int		home_len;
	int		pwd_len;
	int		extra_symbols;

	extra_symbols = 4;
	home = find_var(g_msh->env, "HOME");
	pwd = find_var(g_msh->env, "PWD");
	home_len = ft_strlen(home);
	pwd_len = ft_strlen(pwd);
	if (ft_strnequ(pwd, home, home_len))
		return (pwd_len - home_len + extra_symbols + 1);
	else
		return (pwd_len + extra_symbols);
}

static void		rl_mc_left(void)
{
	t_rl	*rl;

	rl = g_msh->rl;
	if (rl->cur_pos > 0 && rl->line[rl->cur_pos - 1] != '\n')
	{
		ft_printf("%s", g_msh->cmd->left);
		rl->cur_pos--;
	}
}

static void		rl_mc_right(void)
{
	int		term_width;
	int		prompt_width;
	t_wsize	wsize;
	t_rl	*rl;

	rl = g_msh->rl;

	if (rl->cur_pos >= rl->line_len)
		return;
	ioctl(0, TIOCGWINSZ, &wsize);
	term_width = wsize.ws_col;
	prompt_width = rl_calc_prompt_len();
	if ((prompt_width + rl->cur_pos) % term_width != 0)
	{
		ft_printf("%s", g_msh->cmd->right);
		rl->cur_pos++;	
	}
	else if ((prompt_width + rl->cur_pos) % term_width == 0)
	{
		ft_printf("%s%s", g_msh->cmd->cur_start, g_msh->cmd->down);
		rl->cur_pos++;	
	}
}


void		rl_move_cur(long ch)
{
	if (!(ch == LEFT || ch == RIGHT))
		return ;
	if (ch == LEFT)
		rl_mc_left();
	else if (ch == RIGHT)
		rl_mc_right();
}

