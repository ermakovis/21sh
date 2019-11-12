/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:09:19 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 16:09:20 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	bin_cd_error(char *message, char ***tokens, char **path)
{
	ft_dprintf(STDERR_FILENO, "%s: cd: %s\n", g_msh->shell_name, message);
	if (tokens && *tokens)
		ft_free_table(tokens);
	ft_memdel((void**)path);
	return (BIN_FAILURE);
}

static int	bin_cd_action(char *path)
{
	char cwd[PATH_MAX + 1];

	if (!path && !*path)
		return (BIN_SUCCESS);
	if (chdir(path) == -1)
		return (BIN_FAILURE);
	set_var(g_msh->env, "OLDPWD", find_var(g_msh->env, "PWD"));
	set_var(g_msh->env, "PWD", getcwd(cwd, PATH_MAX));
	return (BIN_SUCCESS);
}

static int	bin_cd_getpath(char *token, char **path)
{
	char *ret;

	if (!token || ft_strequ(token, "+"))
	{
		if (!(ret = find_var(g_msh->env, "HOME")))
			return (BIN_FAILURE);
	}
	else if (ft_strequ(token, "-"))
	{
		if (!(ret = find_var(g_msh->env, "OLDPWD")))
			return (BIN_FAILURE);
	}
	else
		ret = token;
	if (ft_strlen(ret) > PATH_MAX)
		return (BIN_FAILURE);
	if (!(ret = ft_strdup(ret)))
		cleanup(-1, "Malloc failed at bin_cd_getpath");
	*path = ret;
	return (BIN_SUCCESS);
}

int			bin_cd(t_list *list)
{
	int		flag_ret;
	char	**tokens;
	char	*path;
	int		flags;

	ex_tokens(&tokens, list);
	if ((flag_ret = ft_parse_options("LP", &tokens[1], &flags)) == -1)
		return (bin_print_error("Incorrect option", "cd", &tokens));
	if (ft_table_size(&tokens[flag_ret + 1]) > 1)
		return (bin_print_error("Too many options", "cd", &tokens));
	if (bin_cd_getpath(tokens[flag_ret + 1], &path) == BIN_FAILURE)
		return (bin_print_error("Incorrect path", "cd", &tokens));
	if (bin_cd_cdpath(&path) == BIN_FAILURE)
		return (bin_cd_error("Failed to get path", &tokens, &path));
	if (bin_cd_canon(&path, flags) == BIN_FAILURE)
		return (bin_cd_error("Failed to get path", &tokens, &path));
	if (bin_cd_action(path) == BIN_FAILURE)
		return (bin_cd_error("Failed to change dir", &tokens, &path));
	ft_free_table(&tokens);
	ft_memdel((void**)&path);
	return (BIN_SUCCESS);
}
