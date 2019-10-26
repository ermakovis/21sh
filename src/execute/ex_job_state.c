#include "msh.h"

void	ex_job_state_check(t_job *job)
{
		int ret;
		int	status;

		if (!(ret = waitpid(job->pid, &status,\
			WNOHANG | WCONTINUED | WUNTRACED)))
			return ;
		if (WIFSTOPPED(status))
		{
			job->state = STOPPED;
			job->status = WSTOPSIG(status);
		}
		else if (WIFEXITED(status))
		{
			job->state = DONE;
			job->status = WEXITSTATUS(status);
		}
		else if (ret == -1)
		{
			job->state = DONE;
			job->status = 0;
		}
		else if (WIFSIGNALED(status))
		{
			job->state = SIGNALED;
			job->status = WTERMSIG(status);
		}
		else
		{
			job->state = RUNNING;
			job->status = 0;
		}
}

void	ex_job_state(void)
{
	t_list	*list;

	list = g_msh->jobs;
	while (list)
	{
		ex_job_state_check(list->content);
		list = list->next;
	}
}

