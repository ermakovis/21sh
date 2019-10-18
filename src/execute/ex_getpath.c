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

static int	ex_getpath_check(char *path)
{
	int		ret;

	if (!ft_test_path(path))
	{
		ft_dprintf(2, "%s: %s: command not found\n", g_msh->shell_name, path);
		return (FAILURE);
	}
	if (!(ft_test_path(path) & 1))
	{
		ft_dprintf(2, "%s: %s: permission denied\n", g_msh->shell_name, path);
		return (FAILURE);
	}
	if (ft_item_type(path) == 2)
	{
		ft_dprintf(2, "%s: %s: is a directory\n", g_msh->shell_name, path);
		return (FAILURE);
	}
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
	if (!ft_strchr(token, '/') &&\
		(list = ft_lst_find(g_msh->hash, token, &cmp_hash)))
	{
		hash = list->content;
		(hash->hits)++;
		if (!(*cmd = ft_strdup(hash->command)))
			cleanup(-1, "Malloc failed at ex_getpath");
	}
	else if (!(*cmd = ft_strdup(token)))
			cleanup(-1, "Malloc failed at ex_getpath");
	if (ex_getpath_check(*cmd) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
