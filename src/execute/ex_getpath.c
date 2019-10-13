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

static char	*ex_exec_join(char *s1, char *s2)
{
	char	*join;
	int		s1len;
	int		s2len;

	if (!s1 && !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(join = ft_strnew(s1len + s2len + 1)))
		return (NULL);
	ft_memcpy(join, s1, s1len);
	if (*(join + s1len) != '/')
		ft_memset(join + s1len, '/', 1);
	ft_memcpy(join + s1len + 1, s2, s2len);
	return (join);
}

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

static int	ex_getpath_cycle(char **paths, char *token, char **cmd)
{
	int		i;

	i = -1;
	while (paths[++i])
	{
		if (ft_strnequ(token, paths[i], ft_strlen(paths[i])))
			*cmd = ft_strdup(token);
		else
			*cmd = ex_exec_join(paths[i], token);
		if (ft_test_path(*cmd))
			break ;
		else
			ft_memdel((void**)cmd);
	}
	if (!(ft_test_path(*cmd) & 1))
	{
		ft_dprintf(2, "%s: permission denied\n", *cmd);
		ft_free_table(&paths);
		return (FAILURE);
	}
	return (SUCCESS);
}

int			ex_getpath(char *token, char **cmd)
{
	int		i;
	char	**paths;
	char	*paths_env;

	if (!token || !*token)
		return (FAILURE);
	if (ft_strchr(token, '/'))
		return (ex_getpath_nopath(token, cmd));
	if (!(paths_env = find_var(g_msh->env, "PATH")))
		return (ex_getpath_nopath(token, cmd));
	if (!(paths = ft_strsplit(paths_env, ':')))
		return (ex_getpath_nopath(token, cmd));
	if (ex_getpath_cycle(paths, token, cmd) == FAILURE)
		return (FAILURE);
	ft_free_table(&paths);
	if (!*cmd)
		return (ex_getpath_nopath(token, cmd));
	return (SUCCESS);
}
