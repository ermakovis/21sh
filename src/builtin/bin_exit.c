/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:09:27 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 16:11:31 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int		bin_exit(t_list *list)
{
	size_t	tokens_count;
	char	**tokens;
	int		return_value;

	return_value = 0;
	tokens_count = ft_lstsize(list);
	ex_tokens(&tokens, list);
	if (tokens_count > 1 && !ft_isnumber(tokens[1]))
	{
		return_value = 2;
		ft_dprintf(2, "%s: exit: Num value required\n", g_msh->shell_name);
	}
	else if (tokens_count > 2)
	{
		return_value = 1;
		ft_dprintf(2, "%s: exit: Too many arguments\n", g_msh->shell_name);
	}
	else if (tokens_count == 2)
		return_value = ft_atoi(tokens[1]);
	ft_free_table(&tokens);
	set_terminal_canon();
	cleanup(return_value, 0);
	return (return_value);
}
