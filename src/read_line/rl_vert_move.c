/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_vert_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:52:52 by tcase             #+#    #+#             */
/*   Updated: 2019/11/07 15:28:29 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void			rl_vert_move(long ch)
{
	int		term_width;
	t_wsize	wsize;

	if (!(ch == UPLINE || ch == DOWNLINE) || g_msh->rl_mode == SEARCH_MODE)
		return ;
	ioctl(0, TIOCGWINSZ, &wsize);
	term_width = wsize.ws_col;
	if (ch == UPLINE)
		rl_vm_up(term_width);
	else if (ch == DOWNLINE)
		rl_vm_down(term_width);
}
