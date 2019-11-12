/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_bg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:08:14 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 16:08:15 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int		bin_bg_failure_message(char *line)
{
	ft_printf("%s: fg: %s\n", g_msh->shell_name, line);
	return (BIN_FAILURE);
}

static int		bin_bg_action(int pos)
{
	t_job	*job;

	if (!(job = find_job(pos)))
		return (bin_bg_failure_message("current: no such job"));
	else
	{
		if ((kill(job->pid, SIGCONT) < 0))
			ft_dprintf(2, "fg: Failed to send continue signal\n");
	}
	return (BIN_SUCCESS);
}

int				bin_bg(t_list *list)
{
	int		tokens_count;
	char	**tokens;
	int		ret;

	if (ft_lstsize(g_msh->jobs) == 0)
		return (bin_bg_failure_message("current: no such job"));
	ret = BIN_FAILURE;
	tokens_count = ft_lstsize(list);
	ex_tokens(&tokens, list);
	if (tokens_count == 1)
	{
		list = g_msh->jobs;
		while (list->next)
			list = list->next;
		ret = bin_bg_action(((t_job*)list->content)->num);
	}
	else if (tokens_count > 2)
		ft_dprintf(2, "%s: fg: Too many arguments\n", g_msh->shell_name);
	else if (ft_isnumber(tokens[1]))
		ret = bin_bg_action(ft_atoi(tokens[1]));
	ft_free_table(&tokens);
	return (ret);
}
