/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:24:29 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 20:24:29 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void		ut_signal_sigint(int sig)
{
	(void)sig;
	if (g_msh->rl_mode == HEREDOC_MODE)
		return ;
	if (g_msh && g_msh->rl)
	{
		rl_jump(LINE_END);
		ft_printf("\n");
		display_prompt();
	}
	ft_printf("%s", g_msh->cmd->highlight_mode_off);
	g_msh->rl_mode = RL_MODE;
	cl_rl_struct();
	init_rl();
}

void		ut_signal_test(int sig)
{
	ft_dprintf(2, "Gotcha %d\n", sig);
}

void		ut_signal_parent(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGINT, ut_signal_sigint);
}

void		ut_signal_child(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
