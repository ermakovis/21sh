/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_small_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:25:28 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 17:25:39 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	msh_setenv(t_list *list)
{
	size_t	tokens_count;
	char	**tokens;

	ex_tokens(list, &tokens);
	tokens_count = ft_table_size(tokens);
	if (tokens_count == 1)
		msh_env(list);
	else if (tokens_count > 3)
		ft_dprintf(2, "setenv: Too many arguments.\n");
	else if (find_var(g_msh->env, tokens[1]))
		set_var(g_msh->env, tokens[1], tokens[2]);
	else
		add_var(tokens[1], tokens[2], &(g_msh->env));
	ft_free_table(&tokens);
}

void	msh_unsetenv(t_list *list)
{
	size_t	tokens_count;
	char	**tokens;

	ex_tokens(list, &tokens);
	tokens_count = ft_table_size(tokens);
	if (tokens_count == 1)
		ft_dprintf(2, "unsetenv: Not enough arguments.\n");
	else if (tokens_count > 2)
		ft_dprintf(2, "unsetenv: Too many arguments.\n");
	else
		ft_lst_remove_if(&(g_msh->env), tokens[1], &cmp_var, &delete_var);
	ft_free_table(&tokens);
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
