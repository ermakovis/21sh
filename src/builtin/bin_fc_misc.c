/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_fc_misc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:16:00 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 17:13:45 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	bin_fc_edit_create(t_list *list, char **name)
{
	int		name_num;
	int		fd;
	t_stat	stat;

	*name = 0;
	name_num = rand();
	if (!(*name = ft_itoa(name_num)))
		cleanup(-1, "Malloc failed at bin_fc_editor_craete");
	if (lstat(*name, &stat) != -1)
	{
		ft_memdel((void**)name);
		return (bin_fc_edit_create(list, name));
	}
	if ((fd = open(*name, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
	{
		ft_dprintf(2, "%s: failed to open %s\n", g_msh->shell_name, *name);
		return ;
	}
	while (list)
	{
		ft_dprintf(fd, "%s\n", list->content);
		list = list->next;
	}
}

void	bin_fc_edit_read(char *file_name, char **file_content)
{
	int		fd;
	char	buff[PATH_MAX + 1];
	char	*line;
	char	*tmp;
	int		res;

	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		dprintf(2, "%s: %s: can't open file\n", file_name, g_msh->shell_name);
		return ;
	}
	line = 0;
	while ((res = read(fd, &buff, PATH_MAX)) > 0)
	{
		buff[res] = 0;
		tmp = line;
		line = ft_strjoin(line, buff);
		ft_memdel((void**)&tmp);
	}
	*file_content = line;
	if (fd > 0)
		close(fd);
}

size_t	bin_fc_list_find_bynum(char *line)
{
	int		ret;
	int		max;

	max = g_msh->history->content_size;
	ret = ft_atoi(line);
	if (ret <= 0 && max + ret <= 0)
		ret = 1;
	else if (ret <= 0)
		ret = max + ret;
	else if (ret > 0 && ret >= max)
		ret = max;
	return ((size_t)ret);
}

size_t	bin_fc_list_find(char *line)
{
	t_list	*list;
	int		line_len;

	if (!line)
		return (g_msh->history->content_size);
	if (ft_isnumber(line))
		return (bin_fc_list_find_bynum(line));
	if (!(list = g_msh->history->next))
		return (-1);
	line_len = ft_strlen(line);
	while (list)
	{
		if (ft_strnequ(list->content, line, line_len))
			return (list->content_size);
		list = list->next;
	}
	return (-1);
}
