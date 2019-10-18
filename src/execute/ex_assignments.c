/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_assignments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:01:48 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 19:01:48 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static t_list	**ex_ass_get_varlist(t_list *list)
{
	t_token		*token;

	while (list)
	{
		token = list->content;
		if (token->token_type != ASSIGNMENT)
			return (&g_msh->cmd_var);
		list = list->next;
	}
	return (&g_msh->var);
}

void		ex_assignments(t_list **list)
{
	t_token		*token;
	char		*line;
	int			eq_pos;
	t_list		**var_list;

	if (!*list)
		return ;
	ft_lstdel(&g_msh->cmd_var, &delete_var);
	var_list = ex_ass_get_varlist(*list);
	while (*list && ((t_token*)(*list)->content)->token_type == ASSIGNMENT)
	{
		token = (*list)->content;
		line = token->line;
		eq_pos = ft_strclen(line, "=") - 1;
		line[eq_pos] = 0;
		if (find_var(*var_list, line))
			set_var(*var_list, line, line + eq_pos + 1);
		else
			add_var(line, line + eq_pos + 1, var_list);
		ft_lstpop(list, &del_token);
	}
	ft_lstiter(g_msh->cmd_var, &print_var);
}
