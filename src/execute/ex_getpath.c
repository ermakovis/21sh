/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:12:38 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 19:13:26 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	ex_getpath_nopath(char *token, char **cmd)
{
	int		item_type;

	if (!ft_test_path(token))
	{
		ft_dprintf(2, "%s: %s: command not found\n", g_msh->shell_name, token);
		return (FAILURE);
	}
	if (!(ft_test_path(token) & 1))
	{
		ft_dprintf(2, "%s: %s: permission denied\n", g_msh->shell_name, token);
		return (FAILURE);
	}
	//if ((item_type = ft_item_type(token)) == -1)
	//{
	//	ft_dprintf(2, "%s: %s: wrong item type\n", g_msh->shell_name, token);
	//	return (FAILURE);
	//}
	if (item_type == 2)
	{
		ft_dprintf(2, "%s: %s: is a directory\n", g_msh->shell_name, token);
		return (FAILURE);
	}
	if (!(*cmd = ft_strdup(token)))
		cleanup(-1, "Malloc failed at ex_getpath_nopath");
	return (SUCCESS);
}

int			ex_getpath(char *token, char **cmd)
{
	t_list	*list;
	t_hash	*hash;
	int		i;

	*cmd = 0;
	if (!token || !*token)
		return (FAILURE);
	if (ft_strchr(token, '/'))
		return (ex_getpath_nopath(token, cmd));
	if (list = ft_lst_find(g_msh->hash, token, &cmp_hash))
	{
		hash = list->content;
		(hash->hits)++;
		if (!(*cmd = ft_strdup(hash->command)))
			cleanup(-1, "Malloc failed at ex_getpath");
	}
	if (!*cmd)
		return (ex_getpath_nopath(token, cmd));
	return (SUCCESS);
}
