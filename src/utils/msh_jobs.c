#include "msh.h"

static void msh_jobs_reg(void)
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

void	msh_jobs(t_list *list)
{
	int		tokens_count;
	char	**tokens;

	tokens_count = ft_lstsize(list);
	ex_tokens(list, &tokens);
	if (tokens_count == 1)
		msh_jobs_reg();
	
	ft_free_table(&tokens);
}
