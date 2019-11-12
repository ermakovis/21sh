/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_job_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:29:54 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 20:10:33 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	ex_job_state_assign(t_job *job, int state, int status)
{
	job->state = state;
	job->status = status;
}

void		ex_job_state_check(t_job *job)
{
	int ret;
	int	status;

	ret = 0;
	status = 0;
	if (!(ret = waitpid(job->pid, &status,\
					WNOHANG | WCONTINUED | WUNTRACED)))
		return ;
	if (ret == 0)
		return ;
	if (WIFSTOPPED(status))
		ex_job_state_assign(job, STOPPED, WSTOPSIG(status));
	else if (WIFEXITED(status))
		ex_job_state_assign(job, DONE, WEXITSTATUS(status));
	else if (ret == -1)
		ex_job_state_assign(job, DONE, 0);
	else if (WIFSIGNALED(status))
		ex_job_state_assign(job, SIGNALED, WTERMSIG(status));
	else
		ex_job_state_assign(job, RUNNING, 0);
}

void		ex_job_state(void)
{
	t_list	*list;

	list = g_msh->jobs;
	while (list)
	{
		ex_job_state_check(list->content);
		list = list->next;
	}
}
