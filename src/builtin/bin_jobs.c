#include "msh.h"

#define JOBS_SHORT (1 << 1)
#define JOBS_FULL 1 

static void bin_jobs_line(t_job *job, int options)
{
	char	*status[] = {"Running", "Stopped", "Signaled", "Error", "Done"}; 
	
	if (options & JOBS_SHORT)
		ft_printf("%d\n", job->pid);
	else if (options & JOBS_FULL)
		ft_printf("[%d]%c %5d %-20s%s\n", job->num, job->sign, job->pid,\
			status[job->state], job->cmd_line);
	else
		ft_printf("[%d]%c %-20s%s\n", job->num, job->sign,  \
			status[job->state], job->cmd_line);
}

static void bin_jobs_full(int options)
{
	t_list *list;

	list = g_msh->jobs;
	while (list)
	{
		bin_jobs_line(list->content, options);
		list = list->next;
	}
}

static int bin_jobs_specifics(char **table, int options)
{
	int		i;
	t_job	*job;
	int		ret;

	i = -1;
	ret = BIN_SUCCESS;
	while (table[++i])
	{
		if (!ft_isnumber(table[i]))
		{
			ft_dprintf(2, "%s: jobs: %s: Number expected\n",\
				g_msh->shell_name, table[i]);
			ret = BIN_FAILURE;
		}
		else if (!(job = find_job(ft_atoi(table[i]))))
		{
			ft_dprintf(2, "%s: jobs: %s: no such job\n",\
				g_msh->shell_name, table[i]);
			ret = BIN_FAILURE;
		}
		else
			bin_jobs_line(job, options);
	}
	return (ret);
}

int		bin_jobs(t_list *list)
{
	char	**tokens;
	int		options;
	int		i;
	int		ret;

	ret = BIN_SUCCESS;
	ex_tokens(&tokens, list);
	ex_job_state();
	ex_job_put_signes();
	i = 1;
	if ((ret = ft_parse_options("lp", &tokens[i], &options)) == -1)
		return (bin_print_error("Wrong parameter", "jobs", &tokens));
	i += ret;
	if (!tokens[i])
		bin_jobs_full(options);
	else if (bin_jobs_specifics(&tokens[i], options) == BIN_FAILURE);
		ret = BIN_FAILURE;
	ex_job_del_completed();
	ft_free_table(&tokens);
	return (ret);
}
