#include "msh.h"

void		init_history_store(char *line)
{
	t_list	*list;
	char	**arr;
	int		i;

	i = -1;
	if (!line)
		return ;
	if (!(arr = ft_strsplit(line, '\n')))
		cleanup(-1, "Malloc failed at init_history_store");
	while (arr[++i])
	{
		if (!(list = (t_list*)ft_memalloc(sizeof(t_list))))
			cleanup(-1, "Malloc failed at init_history_store");
		if (!(list->content = (void*)ft_strdup(arr[i])))
			cleanup(-1, "Malloc failed at init_history_store");
		ft_lstadd_last(&(g_msh->history), list);
	}
	rl_history_putnumbers();
	ft_free_table(&arr);
}

void		init_history(void)
{
	int		fd;
	char	*path;
	char	buff[PATH_MAX + 1];
	char	*line;
	int		res;

	line = NULL;
	path = ft_strdup(HISTORY_PATH);
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		dprintf(2, "%s: can't open history's file\n", g_msh->shell_name);
		ft_memdel((void**)&path);
		return ;
	}
	ft_memdel((void**)&path);
	while ((res = read(fd, &buff, PATH_MAX)) > 0)
	{
		buff[res] = 0;
		path = line;
		line = ft_strjoin(line, buff);
		ft_memdel((void**)&path);
	}
	close(fd);
	init_history_store(line);
	ft_memdel((void**)&line);
}
