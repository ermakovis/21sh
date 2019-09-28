#include "msh.h"

/*
**	TODO: job recognition by cmd_line
**	NOTE: mb a little overreaction on SIGCONT fail
*/

void		msh_fg_action(int pos)
{
	t_list	*list;
	t_job	*job;

	if (!(list = ft_lst_num(g_msh->jobs, pos)))
		ft_dprintf(2, "fg: %d: no such job\n");
	else
	{
		job = list->content;
		tcsetpgrp(STDOUT_FILENO, job->pid);
		if ((kill(job->pid, SIGCONT) < 0))
			ft_dprintf(2, "fg: Failed to send continue signal\n");
		ex_wait(job);
		tcsetpgrp(STDOUT_FILENO, g_msh->pid);
		tcsetattr(STDOUT_FILENO, TCSADRAIN, g_msh->original_state);
	}
}

void		msh_fg(t_list *list)
{
	int		tokens_count;
	char	**tokens;

//	ex_job_check(1);
	tokens_count = ft_lstsize(list);
	ex_tokens(list, &tokens);
	if (tokens_count == 1)
		msh_fg_action(ft_lstsize(g_msh->jobs) - 1);
	else if (tokens_count > 2)
		ft_dprintf(2, "fg: Too many arguments\n"); 
	else if (ft_isnumber(tokens[1]))
		msh_fg_action(ft_atoi(tokens[1]));
}
