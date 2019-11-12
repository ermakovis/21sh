/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:33:50 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 20:33:56 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*init_hash_join(char *s1, char *s2)
{
	char	*join;
	int		s1len;
	int		s2len;

	if (!s1 && !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(join = ft_strnew(s1len + s2len + 2)))
		return (NULL);
	ft_memcpy(join, s1, s1len);
	if (*(join + s1len) != '/')
		ft_memset(join + s1len, '/', 1);
	ft_memcpy(join + s1len + 1, s2, s2len);
	return (join);
}

static void	init_hash_add(t_dir *entry, char *path)
{
	char	*short_name;
	char	*command;

	if (!(short_name = ft_strdup(entry->d_name)))
		cleanup(-1, "Malloc failed at init_hash_add");
	if (!(command = init_hash_join(path, entry->d_name)))
		cleanup(-1, "Malloc failed at init_hash_add");
	add_hash(command, short_name);
}

static void	init_hash_cycle(char *path)
{
	DIR		*dir;
	t_dir	*entry;

	if (!(dir = opendir(path)))
		return ;
	while ((entry = readdir(dir)))
		if (ft_strcmp(entry->d_name, "..") && ft_strcmp(entry->d_name, "."))
			init_hash_add(entry, path);
	closedir(dir);
}

void		init_hash(void)
{
	char	**paths;
	char	*paths_env;
	int		i;

	i = -1;
	if (!(paths_env = find_var(g_msh->env, "PATH")))
		return ;
	if (!(paths = ft_strsplit(paths_env, ':')))
		return ;
	while (paths[++i])
		init_hash_cycle(paths[i]);
	ft_free_table(&paths);
}
