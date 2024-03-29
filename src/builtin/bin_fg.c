/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_fg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:52:49 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 15:56:01 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int		bin_fg_failure_message(char *line)
{
	ft_printf("%s: fg: %s\n", g_msh->shell_name, line);
	return (BIN_FAILURE);
}

static int		bin_fg_action(int pos)
{
	t_job	*job;
	int		status;

	status = BIN_SUCCESS;
	if (!(job = find_job(pos)))
		return (bin_fg_failure_message("current: no such job"));
	else
	{
		tcsetpgrp(STDOUT_FILENO, job->pid);
		if ((kill(job->pid, SIGCONT) < 0))
			ft_dprintf(2, "fg: Failed to send continue signal\n");
		status = ex_wait(job);
		status = ex_exit_status(status);
		ex_set_return_var(status);
		tcsetpgrp(STDOUT_FILENO, g_msh->pid);
		tcsetattr(STDOUT_FILENO, TCSADRAIN, g_msh->original_state);
	}
	return (status);
}

int				bin_fg(t_list *list)
{
	int		tokens_count;
	char	**tokens;
	int		ret;

	ret = BIN_FAILURE;
	if (ft_lstsize(g_msh->jobs) == 0)
		return (bin_fg_failure_message("current: no such job"));
	tokens_count = ft_lstsize(list);
	ex_tokens(&tokens, list);
	if (tokens_count == 1)
	{
		list = g_msh->jobs;
		while (list->next)
			list = list->next;
		ret = bin_fg_action(((t_job*)list->content)->num);
	}
	else if (tokens_count > 2)
		ft_dprintf(2, "%s: fg: Too many arguments\n", g_msh->shell_name);
	else if (ft_isnumber(tokens[1]))
		ret = bin_fg_action(ft_atoi(tokens[1]));
	ft_free_table(&tokens);
	return (ret);
}
