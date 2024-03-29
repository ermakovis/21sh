/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:50:25 by tcase             #+#    #+#             */
/*   Updated: 2019/11/07 15:26:56 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void			rl_copy_paste(void)
{
	char	*line;

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
	if (!(ch == VMODE || ch == PASTE || g_msh->rl_mode == SEARCH_MODE))
		return ;
	if (ch == VMODE)
		rl_copy_movements();
	else if (ch == PASTE)
		rl_copy_paste();
}
