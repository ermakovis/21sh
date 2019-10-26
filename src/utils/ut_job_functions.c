#include "msh.h"

int			cmp_job(t_job *job, t_job *ref)
{
	return (ft_memcmp(job, ref, sizeof(t_job)));
}

t_job		*find_job(int num)
{
	t_list	*list;
	t_job	*job;

	list = g_msh->jobs;	
	while (list)
	{
		job = list->content;
		if (job->num == num)
			return (job);
		list = list->next;
	}
	return (0);
}

void		del_job(void *content, size_t content_size)
{
	t_job	*job;

	(void)content_size;
	job = content;
	ft_memdel((void**)&job->cmd_line);
	ft_memdel((void**)&content);
}

t_job		*get_job(pid_t pid, char *cmd_line)
{
	t_job	*job;
	t_list	*list;

	if (!(job = ft_memalloc(sizeof(t_job))))
		cleanup(-1, "Malloc failed at add_job");
	list = g_msh->jobs;
	if (!list)
		job->num = 1;
	else
	{
		while (list->next)
			list = list->next;
		job->num = ((t_job*)list->content)->num + 1;
	}
	job->pid = pid;
	job->cmd_line = cmd_line;
	return (job);
}

void		add_job(t_list **alist, t_job *job)
{
	t_list	*list;

	if (!(list = ft_lstnew(job, sizeof(t_job))))
		cleanup(-1, "Malloc failed at add_job #2");
	ft_lstadd_last(alist, list);
	ex_job_put_signes();
}
