/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_terminal_mods.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:40:12 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 18:40:40 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	set_terminal_raw(void)
{
	t_term	raw;

	if (!isatty(STDIN_FILENO))
		return ;
	if (tcgetattr(0, &raw) == -1)
		cleanup(-1, "Failed to save terminal original state");
	raw.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, &raw) == -1)
		cleanup(-1, "Failed to set terminal to raw mode");
}

void	set_terminal_canon(void)
{
	if (!isatty(STDIN_FILENO))
		return ;
	if (tcsetattr(0, TCSANOW, g_msh->original_state) == -1)
		cleanup(-1, "Failed to set terminal to canon mode");
}
