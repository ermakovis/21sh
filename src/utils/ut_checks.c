/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:32:05 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 20:32:06 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int		ut_check_execute(char const *path)
{
	t_stat	sb;
	int		ret;
	int		res;

	ret = 0;
	res = lstat(path, &sb);
	if (res == -1)
		ft_dprintf(STDERR_FILENO, "%s: %s: not found\n",\
				g_msh->shell_name, path);
	else if (S_ISDIR(sb.st_mode))
		ft_dprintf(STDERR_FILENO, "%s: %s: is a directory\n",\
				g_msh->shell_name, path);
	else if (res == 0 && sb.st_mode & S_IXUSR)
		ret = 1;
	else
		ft_dprintf(STDERR_FILENO, "%s: %s: permission denied\n",\
				g_msh->shell_name, path);
	return (ret);
}

int		ut_check_write(char const *path)
{
	t_stat	sb;
	int		ret;
	int		res;

	ret = 0;
	res = lstat(path, &sb);
	if (res == -1)
		ft_dprintf(STDERR_FILENO, "%s: %s: not found\n",\
				g_msh->shell_name, path);
	else if (S_ISDIR(sb.st_mode))
		dprintf(STDERR_FILENO, "%s: %s: is a directory\n",\
				g_msh->shell_name, path);
	else if (res == 0 && sb.st_mode & S_IWUSR)
		ret = 1;
	else
		dprintf(STDERR_FILENO, "%s: %s: permission denied\n",\
				g_msh->shell_name, path);
	return (ret);
}

int		ut_check_dir(char *path)
{
	char	cwd[PATH_MAX];
	int		ret;

	if (!(ret = ft_test_path(path)))
		return (0);
	else if (ft_item_type(path) != 2)
		return (0);
	else if (!(ret & 1))
		return (0);
	return (1);
}
