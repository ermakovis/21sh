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

int			ex_check_executable(char *path)
{
	if (!(ft_test_path(path) & 1))
	{
		ft_dprintf(2, "%s: permission denied\n", path);
		return (FAILURE);
	}
	return (SUCCESS);
}

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

static void	ex_get_full_path(char *path, char *token, char **cmd)
{
	if (ft_strnequ(token, path, ft_strlen(path)))
		*cmd = ft_strdup(token);
	else
		*cmd = ex_exec_join(path, token);
}

static int	ex_getpath_nopath(char *token, char **cmd)
{
	int		item_type;

	if (!ft_test_path(token))
	{
		ft_dprintf(2, "%s: %s: command not found\n", g_msh->shell_name, token);
		return (FAILURE);
	}
	if ((item_type = ft_item_type(token)) == -1)
	{
		ft_dprintf(2, "%s: %s: wrong item type\n", g_msh->shell_name, token);
		return (FAILURE);
	}
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
	int		i;
	char	**paths;
	char	*paths_env;

	if (!token || !*token)
		return (FAILURE);
	if (!(paths_env = find_var(g_msh->env, "PATH")))
		return (ex_getpath_nopath(token, cmd));
	if (!(paths = ft_strsplit(paths_env, ':')))
		return (ex_getpath_nopath(token, cmd));
	i = -1;
	while (paths[++i])
	{
		ex_get_full_path(paths[i], token, cmd);
		if (ft_test_path(*cmd))
			break ;
		else
			ft_memdel((void**)cmd);
	}
	ft_free_table(&paths);
	if (!*cmd)
		return (ex_getpath_nopath(token, cmd));
	return (SUCCESS);
}
