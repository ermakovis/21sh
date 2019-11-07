/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:48:44 by tcase             #+#    #+#             */
/*   Updated: 2019/11/07 16:56:29 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void			init_rl(void)
{
	t_rl	*new_rl;
	size_t	size;

	size = sizeof(t_rl);
	if (!(new_rl = (t_rl*)malloc(size)))
		cleanup(-1, "Failed to malloc for rl structure\n");
	ft_bzero(new_rl, size);
	if (!(new_rl->line = ft_strnew(MSH_BUFF_SIZE)))
		cleanup(-1, "Failed to malloc for rl's new string\n");
	new_rl->history = -1;
	g_msh->rl = new_rl;
}

static void		rl_switch(long ch)
{
	rl_copy(ch);
	rl_tab(ch);
	rl_history(ch);
	if (ch == CTRL_R)
		rl_history_search(ch);
	rl_move_cur(ch);
	rl_vert_move(ch);
	rl_jump(ch);
	rl_del_char(ch);
	if (ft_isprint(ch))
		rl_print_char(ch);
}

static int		rl_endline_check(void)
{
	if (g_msh->rl->line_len == 0 && g_msh->rl_mode == RL_MODE)
		cleanup(0, "");
	if (g_msh->rl->line_len == 0 && g_msh->rl_mode == HEREDOC_MODE)
		return (0);
	return (1);
}

int				read_line(int mode)
{
	long	ch;
	int		ret;

	init_rl();
	g_msh->rl_mode = mode;
	set_terminal_raw();
	while (get_char(&ch))
	{
		if (ch == 4 && !rl_endline_check())
			return (FAILURE);
		else if (ch == '\n')
		{	
			if ((ret = rl_newline_check(g_msh->rl->line, mode)) == 2)
				return (FAILURE); 
			if (ret == 1)
				continue ;
			rl_jump(LINE_END);
			rl_print_char('\n');
			rl_add_history();
			break ;
		}
		else
			rl_switch(ch);
	}
	set_terminal_canon();
	return (SUCCESS);
}
