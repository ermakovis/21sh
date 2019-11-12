/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:33:04 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 20:33:24 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	init_alias_getpath(char **path)
{
	char	*ret;

	if (!(ret = find_var(g_msh->env, "HOME")))
	{
		ft_dprintf(2, "%s: failed to get home path\n", g_msh->shell_name);
		return (0);
	}
	if (ret[ft_strlen(ret)] == '/')
		if (!(ret = ft_powerjoin("%s%s", ret, ".42sh_alias")))
			cleanup(-1, "Malloc failed init_alias_getpath");
	if (ret[ft_strlen(ret)] != '/')
		if (!(ret = ft_powerjoin("%s/%s", ret, ".42sh_alias")))
			cleanup(-1, "Malloc failed init_alias_getpath");
	*path = ret;
	return (1);
}

static int	init_alias_getcontent(char ***path, int fd)
{
	int		res;
	char	buff[PATH_MAX + 1];
	char	*content;
	char	**ret;

	content = 0;
	while ((res = read(fd, &buff, PATH_MAX)) > 0)
	{
		buff[res] = 0;
		if (!(content = ft_powerjoin("%f%s", &content, buff)))
			cleanup(-1, "Malloc failed at init_alias");
	}
	if (!(ret = ft_strsplit(content, '\n')))
		cleanup(-1, "Malloc failed at init_alias_getcontent");
	*path = ret;
	ft_memdel((void**)&content);
	return (1);
}

static void	init_alias_process(char **content)
{
	int		i;
	int		ret;
	t_list	*list;
	char	*line;

	i = -1;
	line = 0;
	while (content[++i])
	{
		if (line && !(line = ft_powerjoin("%f\n%s", &line, content[i])))
			cleanup(-1, "Malloc failed at init_history");
		if (!line && !(line = ft_powerjoin("%f%s", &line, content[i])))
			cleanup(-1, "Malloc failed at init_history");
		if (!(ret = init_history_store_valid(line)))
		{
			if (ft_strnequ(line, "alias ", 6))
				bin_alias_action(line + 6);
			ft_memdel((void**)&line);
		}
		if (ret == 2)
			return ;
	}
}

void		init_alias(void)
{
	int		fd;
	char	*path;
	char	**content;

	if (!init_alias_getpath(&path))
		return ;
	content = 0;
	if ((fd = open(path, O_RDONLY)) == -1)
		ft_dprintf(2, "%s: Failed to open alias file\n", g_msh->shell_name);
	else if (!init_alias_getcontent(&content, fd))
		;
	else
		init_alias_process(content);
	ft_memdel((void**)&path);
	ft_free_table(&content);
	close(fd);
}
