#include "msh.h"

void				ut_signal_sigint(int sig)
{
	(void)sig;
	if (g_msh && g_msh->rl && !g_msh->rl->status)
	{
		rl_jump(LINE_END);
		ft_printf("\n");
		display_prompt();
	}
	ft_printf("%s", g_msh->cmd->highlight_mode_off);
	cl_rl_struct();
	init_rl();
}

void		ut_signal_parent(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGWINCH, SIG_IGN);
	signal(SIGINT, ut_signal_sigint);
	signal(SIGCHLD, SIG_IGN);
}

void		ut_signal_child(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}
