#include "msh.h"

/*
**	TODO: options, plus_sign
*/
static void bin_jobs_reg(void)
{
	t_list	*list;
	t_job	*job;
	int		i;

	i = 1;
	list = g_msh->jobs;
	while (list)
	{
		job = list->content;
		ft_printf("[%d] %d   %s\n", i, job->pid, job->cmd_line);
		i++;
		list = list->next;
	}
}

int		bin_jobs(t_list *list)
{
	int		tokens_count;
	char	**tokens;


	if (!ft_lstsize(g_msh->jobs))
		return (1);
	tokens_count = ft_lstsize(list);
	ex_tokens(&tokens, list);
	if (tokens_count == 1)
		bin_jobs_reg();
	ft_free_table(&tokens);
	return (SUCCESS);
}
