#include "msh.h"

/*
**	TODO: job recognition by cmd_line
**	NOTE: mb a little overreaction on SIGCONT fail
*/

static int		bin_fg_action(int pos)
{
	t_list	*list;
	t_job	*job;
	int		status;

	status = SUCCESS;
	if (!(list = ft_lst_num(g_msh->jobs, pos)))
	{
		ft_dprintf(2, "%s: fg: %d: no such job\n", g_msh->shell_name);
		status = FAILURE;
	}
	else
	{
		job = list->content;
		tcsetpgrp(STDOUT_FILENO, job->pid);
		if ((kill(job->pid, SIGCONT) < 0))
			ft_dprintf(2, "fg: Failed to send continue signal\n");
		status = ex_wait(job);
		status = ex_exit_status(status);
		ex_set_return_var(status);
		tcsetpgrp(STDOUT_FILENO, g_msh->pid);
		tcsetattr(STDOUT_FILENO, TCSADRAIN, g_msh->original_state);
	}
	return (status);
}

int		bin_fg(t_list *list)
{
	int		tokens_count;
	char	**tokens;
	int		ret;

	ret = FAILURE;
	//ex_job_check(1);
	tokens_count = ft_lstsize(list);
	ex_tokens(&tokens, list);
	if (tokens_count == 1)
		ret = bin_fg_action(ft_lstsize(g_msh->jobs) - 1);
	else if (tokens_count > 2)
		ft_dprintf(2, "%s: fg: Too many arguments\n", g_msh->shell_name); 
	else if (ft_isnumber(tokens[1]))
		ret = bin_fg_action(ft_atoi(tokens[1]));
	ft_free_table(&tokens);
	return (ret);
}
