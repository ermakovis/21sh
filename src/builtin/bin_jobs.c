#include "msh.h"

/*
**	TODO: options, plus_sign
*/

#define JOBS_NORMAL 0
#define JOBS_BRIEF 1
#define JOBS_FULL 2

static void bin_jobs_line(t_list *list, int option)
{
	t_job *job;

	job = list->content;
	if (option != JOBS_BRIEF)
		ft_printf("%d", 1);
	if (option != JOBS_BRIEF)
		ft_printf("+ ");
	if (option != JOBS_NORMAL)
		ft_printf("%d", job->pid);
	if (option != JOBS_BRIEF)
	{
		if (job->status == RUNNING)
			ft_printf(" %s %s", " Running ", job->cmd_line);
		else if (job->status == STOPPED)
			ft_printf(" %s %s", " Stopped ", job->cmd_line);
		else if (job->status == ERROR)
			ft_printf(" %s %s", " ERROR ", job->cmd_line);
		else if (job->status == SIGNALED)
			ft_printf(" %s %s", " Signaled ", job->cmd_line);
		if (job->status == DONE)
		{
			ft_printf(" %s %s", " Done ", job->cmd_line);
			ft_lst_remove(&g_msh->jobs, list, &del_job);
		}
	}
	ft_printf("\n");
}

static void bin_jobs_full(int option)
{
	t_list *list;

	list = g_msh->jobs;
	while (list)
	{
		bin_jobs_line(list, option);
		list = list->next;
	}
}

int		bin_jobs(t_list *list)
{
	char	**tokens;
	int		option;
	int		i;

	if (!ft_lstsize(g_msh->jobs))
		return (BIN_SUCCESS);
	option = JOBS_NORMAL;
	i = 0;
	ex_tokens(&tokens, list);
	ex_job_state();
	if (!tokens[i + 1])
		bin_jobs_full(option);
	ft_free_table(&tokens);
	return (BIN_SUCCESS);
}
