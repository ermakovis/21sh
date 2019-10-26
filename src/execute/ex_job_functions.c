#include "msh.h"

void	ex_job_put_signes(void)
{
	t_list		*list;
	t_job		*job;

	list = g_msh->jobs;
	while (list)
	{
		job = list->content;
		if (!list->next)
			job->sign = '+';
		else if (!list->next->next)
			job->sign = '-';
		else
			job->sign = ' ';
		list = list->next;
	}
}

void	ex_job_del_completed(void)
{
	t_list	*list;
	t_job	*job;

	list = g_msh->jobs;
	while (list)
	{
		job = list->content;
		if (job->state == DONE)
		{
			ft_lst_remove(&g_msh->jobs, list, &del_job);
			list = g_msh->jobs;
		}
		else
			list = list->next;
	}
}

void	ex_job_print_completed(void)
{
	t_list	*list;
	t_job	*job;

	list = g_msh->jobs;
	while (list)
	{
		job = list->content;
		if (job->state == DONE)
			ft_printf("[%d] Done%20s\n", job->num, job->cmd_line);
		list = list->next;
	}

}
