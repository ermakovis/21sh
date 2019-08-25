/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_tab_create_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 12:25:22 by tcase             #+#    #+#             */
/*   Updated: 2019/08/25 13:46:16 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int		rl_tab_create_list_first(char *line)
{
	char	*path_str;
	char	**paths;
	DIR		*dir;
	t_dir	*entry;
	int		i;

	i = -1;
	if (!(path_str = find_var(g_msh->env, "PATH")))
		return (FAILURE);
	if (!(paths = ft_strsplit(path_str, ':')))
		cleanup(-1, "rl_tab_create_list_first");
	while (paths[++i])
	{
		if (!(dir = opendir(paths[i])))
			continue ;
		while ((entry = readdir(dir)))
		{
			if (!ft_strncmp(entry->d_name, line, ft_strlen(line)))
				add_str(&(g_msh->rl->tab_items), entry->d_name);
		}
		closedir(dir);
	}
	ft_free_table(&paths);
	if (!(g_msh->rl->tab_items))
		return (FAILURE);
	return (SUCCESS);
}

static char		*rl_tab_getpath(char *line)
{
	int		i;
	int		len;
	char	*ret;

	i = -1;
	len = 0;
	while (line[++i])
	{
		if (line[i] == '/')
			len = i;
	}
	if (len == 0)
		len = ft_strlen(line);
	if (!(ret = ft_strndup(line, len)))
		cleanup(-1, "Malloc failed at rl_tab_getpath");
	return (ret);
}

static char		*rl_tab_get_cmpline(char *path, char *entry)
{
	char	*ret;
	int		path_len;
	int		entry_len;

	path_len = ft_strlen(path);
	entry_len = ft_strlen(entry);
	if (!(ret  = ft_strnew(path_len + entry_len + 1)))
		cleanup(-1, "Malloc failed at rl_tab_get_cmpline");
	ft_memcpy(ret, path, path_len);
	ret[path_len] = '/';
	ft_memcpy(ret + path_len + 1, entry, entry_len);
	return (ret);
}

static int		rl_tab_create_list_secondplus(char *line)
{
	char	*path;
	DIR		*dir;
	t_dir	*entry;
	char	*cmp_line;

	path = rl_tab_getpath(line);
	if (!(dir = opendir(path)))
	{
		ft_memdel((void**)&path);
		return (FAILURE);
	}
	while ((entry = readdir(dir)))
	{
		cmp_line = rl_tab_get_cmpline(path, entry->d_name);
		if (!ft_strncmp(cmp_line, line, ft_strlen(line)))
			add_str(&(g_msh->rl->tab_items), cmp_line);
		ft_memdel((void**)&cmp_line);
	}
	closedir(dir);
	ft_memdel((void**)&path);
	if (!(g_msh->rl->tab_items))
		return (FAILURE);
	return (SUCCESS);
}

int		rl_tab_create_list(void)
{
	char	*word;
	int		word_number;

	word = NULL;
	word_number = 0;
	rl_tab_lastword(&word, &word_number);
	if (word_number == 0)
		return (FAILURE);
	else if (word_number == 1)
		return (rl_tab_create_list_first(word));
	else if (word_number > 1)
		return (rl_tab_create_list_secondplus(word));
	return (SUCCESS);
}
