#include "msh.h"

static void			rl_cm_left(void)
{
	t_rl	*rl;
	char	save;

	rl = g_msh->rl;
	if (rl->cur_pos <= rl->copy_pos)
		ft_printf("%s", g_msh->cmd->highlight_mode_on);
	save = rl->line[rl->cur_pos - 1];
	rl_del_char(BSPACE);
	rl_print_char(save);
	rl_move_cur(LEFT);
	ft_printf("%s", g_msh->cmd->highlight_mode_off);
}

static void			rl_cm_right(void)
{
	t_rl	*rl;
	char	save;

	rl = g_msh->rl;
	if (rl->cur_pos >= rl->copy_pos)
		ft_printf("%s", g_msh->cmd->highlight_mode_on);
	save = rl->line[rl->cur_pos];
	rl_move_cur(RIGHT);
	rl_del_char(BSPACE);
	rl_print_char(save);
	ft_printf("%s", g_msh->cmd->highlight_mode_off);
}

static void			rl_cm_copycut(void)
{
	t_rl	*rl;

	rl = g_msh->rl;
	if (rl->cur_pos == rl->copy_pos)
		return ;
	ft_memdel((void**)&g_msh->rl->copy_buffer);
	if (rl->cur_pos < rl->copy_pos)
		rl->copy_buffer = ft_strndup(rl->line + rl->cur_pos,\
				rl->copy_pos - rl->cur_pos);
	else if (rl->cur_pos > rl->copy_pos)
		rl->copy_buffer = ft_strndup(rl->line + rl->copy_pos,\
				rl->cur_pos - rl->copy_pos);
}

static void			rl_cm_refresh(void)
{
	t_rl	*rl;
	char	*line_save;
	int		i;

	i = -1;
	rl = g_msh->rl;
	if (!(line_save = ft_strdup(rl->line)))
		cleanup(-1, "Malloc failed at rl_cl_refresh");
	rl_jump(LINE_END);
	while (rl->line_len)
		rl_del_char(BSPACE);
	while(line_save[++i])
		rl_print_char(line_save[i]);
	ft_memdel((void**)&line_save);
}

void			rl_copy_movements(void)
{
	long	ch;
	t_rl	*rl;

	rl = g_msh->rl;
	rl->copy_pos = rl->cur_pos;
	while(get_char(&ch))
	{
		if (ch == VMODE)
			break;
		else if (ch == LEFT && rl->cur_pos > 0 &&\
			rl->line[rl->cur_pos - 1] != '\n')
			rl_cm_left();
		else if (ch == RIGHT && rl->cur_pos < rl->line_len)
			rl_cm_right();
		ch = 0;
	}
	rl_cm_copycut();
	rl_cm_refresh();
}
