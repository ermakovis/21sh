#include "msh.h"

void	ex_job_check(int sig)
{
	t_list	*list;
	t_list	*tmp;
	t_job	*job;
	int		count;
	int		status;

	count = 1;
	list = g_msh->jobs;
	while (list)
	{
		job = list->content;
		if (waitpid(job->pid, &status, WNOHANG | WCONTINUED | WUNTRACED) == -1\
			&& sig)
		{
			ft_printf("[%d] Done    %s\n", job->cmd_line);
			tmp = list;
			list = list->next;
			ft_lst_remove(&g_msh->jobs, tmp, &del_job);
		}
		else
			list = list->next;
		count++;
	}
	signal(SIGCHLD, SIG_DFL);
}

int		ex_wait(t_job *job)
{
	int		status;
	t_list	*list;

	status = SUCCESS;
	list = 0;
	waitpid(job->pid, &status, WUNTRACED);
	if (WIFSTOPPED(status))
	{
		if (ft_lst_find(g_msh->jobs, job, &cmp_job) == 0)
			add_job(&g_msh->jobs, job);
		ft_printf("\n[%d] %d Stopped    %s\n", \
			ft_lstget_pos(g_msh->jobs, job, &cmp_job),\
				job->pid, job->cmd_line);
	}
	else
	{
		if ((list = ft_lst_find(g_msh->jobs, job->cmd_line, &cmp_job)) != 0)
			ft_lst_remove(&g_msh->jobs, list, &del_job);
		else
			del_job((void*)job, 0);
	}
	return (status);
}

int			ex_job(pid_t pid, t_ast *ast)
{
	int		status;
	char	*cmd_line;
	t_job	*job;

	cmd_line = ft_strdup("JOB");//there will be function to get full line
	job = get_job(pid, cmd_line);
	setpgid(0,0);
	status = SUCCESS;
	if (ast->bg == 0)
	{
		status = ex_wait(job);
		tcsetpgrp(STDOUT_FILENO, g_msh->pid);
		tcsetattr(STDOUT_FILENO, TCSADRAIN, g_msh->original_state);
	}
	else
	{
		add_job(&g_msh->jobs, job);
		ft_printf("[%d], %d\n", ft_lstsize(g_msh->jobs), job->pid);
	}
	return (status);
}
