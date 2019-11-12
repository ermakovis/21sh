/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_assignments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:01:48 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 20:21:22 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static t_list	**ex_assign_get_varlist(t_list *list)
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

static void		ex_assign_swap(void)
{
	t_list	*list_src;
	t_list	*list_dst;
	t_var	*var_src;
	t_var	*var_dst;
	char	*placeholder;

	list_src = g_msh->cmd_var;
	while (list_src)
	{
		var_src = list_src->content;
		if ((list_dst = ft_lst_find(g_msh->env, var_src->name, &cmp_var)))
		{
			var_dst = list_dst->content;
			placeholder = var_src->value;
			var_src->value = var_dst->value;
			var_dst->value = placeholder;
		}
		list_src = list_src->next;
	}
}

void			ex_assignments_fork(void)
{
	t_list	*cmd_var;
	t_list	*env;
	t_var	*var;

	if (!(cmd_var = g_msh->cmd_var))
		return ;
	while (cmd_var)
	{
		var = cmd_var->content;
		if (find_var(g_msh->env, var->name))
			set_var(g_msh->env, var->name, var->value);
		else
			add_var(var->name, var->value, &g_msh->env);
		cmd_var = cmd_var->next;
	}
}

void			ex_assignments(t_list **list)
{
	t_token		*token;
	char		*line;
	int			eq_pos;
	t_list		**var_list;

	if (!*list)
		return ;
	ex_assign_swap();
	ft_lstdel(&g_msh->cmd_var, &delete_var);
	var_list = ex_assign_get_varlist(*list);
	ft_lstiter(g_msh->cmd_var, &print_var);
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
	ex_assign_swap();
}
