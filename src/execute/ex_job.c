/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_job.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:32:22 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 19:33:10 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int			ex_wait(t_job *job)
{
	int		status;
	t_list	*list;
	int		ret;

	status = 1;
	list = 0;
	ret = waitpid(job->pid, &status, WUNTRACED);
	if (WIFSTOPPED(status))
	{
		job->state = STOPPED;
		if (!(ft_lst_find(g_msh->jobs, job, &cmp_job)))
			add_job(&g_msh->jobs, job);
		ft_printf("\n[%d]%c %d Stopped    %s\n",\
			job->num, job->sign, job->pid, job->cmd_line);
	}
	else
	{
		if ((list = ft_lst_find(g_msh->jobs, job, &cmp_job)))
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

	cmd_line = ft_strdup(((t_token*)ast->token->content)->full_command);
	job = get_job(pid, cmd_line);
	setpgid(0, 0);
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
		ft_printf("[%d] %d\n", job->num, job->pid);
		ft_memdel((void**)&job);
	}
	return (status);
}
