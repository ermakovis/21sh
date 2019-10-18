#include "msh.h"

void	ex_job_state(void)
{
	t_list	*list;
	t_job	*job;
	int		count;
	int		status;
	int		ret;

	list = g_msh->jobs;
	while (list)
	{
		job = list->content;
		ret = waitpid(job->pid, &status, WNOHANG | WCONTINUED | WUNTRACED);
		ft_printf("%d ", ret);
		if (WIFSTOPPED(status))
		{
			job->state = STOPPED;
			job->status = WSTOPSIG(status);
			ft_printf("stopped %d", job->status);
		}
		else if (WIFEXITED(status))
		{
			job->state = DONE;
			job->status = WEXITSTATUS(status);
			ft_printf("exited %d", job->status);
		}
		else if (WIFSIGNALED(status))
		{
			job->state = SIGNALED;
			job->status = WTERMSIG(status);
			ft_printf("signaled %d", job->status);
		}
		ft_printf("\n");
		count++;
		list = list->next;
	}
}

