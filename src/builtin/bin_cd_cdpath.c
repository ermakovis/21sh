/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd_cdpath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:08:55 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 16:09:07 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	bin_cd_cdpath_check(char **path)
{
	char	*tmp;

	if (*path[0] == '/' || *path[0] == '.' || ft_strnequ(*path, "..", 2))
		return (BIN_SUCCESS);
	if (!(tmp = ft_powerjoin("./%s", *path)))
		cleanup(-1, "Malloc failed at bin_cd_path");
	ft_printf("--%s--%d--\n", tmp, ft_strnequ(*path, "./", 2));
	if (ut_check_dir(tmp) == 1)
	{
		ft_memdel((void**)path);
		*path = tmp;
		return (BIN_SUCCESS);
	}
	ft_memdel((void**)&tmp);
	return (BIN_FAILURE);
}

static int	bin_cd_cdpath_cycle(char *line, char **path)
{
	char	*tmp;
	int		len;

	if (!(len = ft_strlen(line)))
		return (BIN_FAILURE);
	if (line[len - 1] == '/')
		if (!(tmp = ft_powerjoin("%s%s", line, *path)))
			cleanup(-1, "Malloc failed at bin_cd_cdpath_cycle");
	if (line[len - 1] != '/')
		if (!(tmp = ft_powerjoin("%s/%s", line, *path)))
			cleanup(-1, "Malloc failed at bin_cd_cdpath_cycle");
	if (ut_check_dir(tmp) == 1)
	{
		ft_memdel((void**)path);
		*path = tmp;
		return (BIN_SUCCESS);
	}
	ft_memdel((void**)&tmp);
	return (BIN_FAILURE);
}

int			bin_cd_cdpath(char **path)
{
	char	*cd_path;
	char	**cd_array;
	int		i;

	i = -1;
	if (*path[0] == '/')
		return (BIN_SUCCESS);
	if (bin_cd_cdpath_check(path) == BIN_SUCCESS)
		return (BIN_SUCCESS);
	if (!(cd_path = find_var(g_msh->env, "CDPATH")))
		return (BIN_FAILURE);
	if (!(cd_array = ft_strsplit(cd_path, ':')))
		cleanup(-1, "Malloc failed at bin_cd_path");
	while (cd_array[++i] &&\
		bin_cd_cdpath_cycle(cd_array[i], path) == BIN_FAILURE)
	{
		ft_free_table(&cd_array);
		return (BIN_SUCCESS);
	}
	ft_free_table(&cd_array);
	return (BIN_SUCCESS);
}
