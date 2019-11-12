/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:41:37 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 15:42:22 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	bin_unset_action(char *name)
{
	int		found;
	t_list	*list;

	found = 0;
	if ((list = ft_lst_find(g_msh->var, name, &cmp_var)))
	{
		ft_lst_remove(&g_msh->var, list, &delete_var);
		found = 1;
	}
	if ((list = ft_lst_find(g_msh->env, name, &cmp_var)))
	{
		ft_lst_remove(&g_msh->env, list, &delete_var);
		found = 1;
	}
	if (found)
		return (BIN_SUCCESS);
	return (BIN_FAILURE);
}

int			bin_unset(t_list *list)
{
	char	**tokens;
	int		i;
	int		ret;

	if (list && !list->next)
		return (BIN_SUCCESS);
	i = -1;
	ret = BIN_SUCCESS;
	ex_tokens(&tokens, list);
	while (tokens[++i])
		if (bin_unset_action(tokens[i]) == BIN_FAILURE)
			ret = BIN_FAILURE;
	return (ret);
}
