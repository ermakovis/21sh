#include "msh.h"

static int		bin_bg_failure_message(char *line)
{
	ft_printf("%s: fg: %s\n", g_msh->shell_name, line);
	return (BIN_FAILURE);
}

static int		bin_bg_action(int pos)
{
	t_list	*list;
	t_job	*job;

	if (ft_lstsize(g_msh->jobs) == 0)
		return (bin_bg_failure_message("current: no such job"));
	if (!(list = ft_lst_num(g_msh->jobs, pos)))
		return (bin_bg_failure_message("current: no such job"));
	else
	{
		job = list->content;
		if ((kill(job->pid, SIGCONT) < 0))
			ft_dprintf(2, "fg: Failed to send continue signal\n");
	}
	return (BIN_SUCCESS);
}

int		bin_bg(t_list *list)
{
	int		tokens_count;
	char	**tokens;
	int		ret;

	ret = BIN_FAILURE;
	tokens_count = ft_lstsize(list);
	ex_tokens(&tokens, list);
	if (tokens_count == 1)
		ret = bin_bg_action(ft_lstsize(g_msh->jobs) - 1);
	else if (tokens_count > 2)
		ft_dprintf(2, "%s: fg: Too many arguments\n", g_msh->shell_name); 
	else if (ft_isnumber(tokens[1]))
		ret = bin_bg_action(ft_atoi(tokens[1]));
	ft_free_table(&tokens);
	return (ret);
}
