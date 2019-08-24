/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_small_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:25:28 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 15:44:17 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	msh_setenv(t_list *list)
{
	size_t	tokens_count;
	char	*name;
	char	*value;

	tokens_count = ft_lstsize(list);
	if (tokens_count == 1)
	{
		msh_env(list);
		return ;
	}
	else if (tokens_count > 3)
	{
		ft_dprintf(2, "setenv: Too many arguments.\n");
		return ;
	}
	name = ((t_token*)list->next->content)->line;
	value = ((t_token*)list->next->next->content)->line;
	if (find_var(g_msh->env, name))
		set_var(g_msh->env, name, value);
	else
		add_var(name, value, &(g_msh->env));
}

void	msh_unsetenv(t_list *list)
{
	size_t	tokens_count;
	char	*name;

	tokens_count = ft_lstsize(list);
	if (tokens_count == 1)
	{
		ft_dprintf(2, "unsetenv: Not enough arguments.\n");
		return ;
	}
	else if (tokens_count > 2)
	{
		ft_dprintf(2, "unsetenv: Too many arguments.\n");
		return ;
	}
	name = ((t_token*)list->next->content)->line;
	ft_lst_remove_if(&(g_msh->env), name, &cmp_var, &delete_var);
}

void	msh_exit(t_list *list)
{
	(void)list;
	set_terminal_canon();
	cleanup(0, NULL);
}

void	msh_env(t_list *list)
{
	size_t	tokens_count;

	tokens_count = ft_lstsize(list);
	if (tokens_count > 1)
	{
		ft_dprintf(2, "exit: Too many arguments.\n");
		return ;
	}
	ft_lstiter(g_msh->env, &print_var);
}
