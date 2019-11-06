#include "msh.h"

int		init_history_store_valid(char *line)
{
	int		ret; 

	if (rl_quotes_check(line) == 0)
		return (1);
	if (rl_bslash_check(line) == 0)
		return (1);
	ret = rl_braces_check(line);
	if (ret == 2)
		ft_dprintf(2, "\n%s: braces are unbalanced\n", g_msh->shell_name);
	return (ret);
}

static int init_history_store_cycle(char **line, char *table)
{
	t_list	*list;
	int		ret;

	if (*line && !(*line = ft_powerjoin("%f\n%s", line, table)))
		cleanup(-1, "Malloc failed at init_history");
	if (!*line && !(*line = ft_powerjoin("%f%s", line, table)))
		cleanup(-1, "Malloc failed at init_history");
	if ((ret = init_history_store_valid(*line)) == 0)
	{
		if (!(list = (t_list*)ft_memalloc(sizeof(t_list))))
			cleanup(-1, "Malloc failed at init_history");
		if (!(list->content = (void*)ft_strdup(*line)))
			cleanup(-1, "Malloc failed at init_history");
		ft_lstadd_last(&(g_msh->history), list);
		ft_memdel((void**)line);
	}
	if (ret == 2)
	{
		ft_dprintf(2, "%s: failed to initialise history\n", g_msh->shell_name);
		ft_lstdel(&g_msh->history, &delete_str);
		return (-1);
	}
	return (0);
}

static void init_history_store(char *line)
{
	t_list	*list;
	char	**arr;
	char	*cycle_line;
	int		i;

	i = -1;
	cycle_line = 0;
	if (!line)
		return ;
	if (!(arr = ft_strsplit(line, '\n')))
		cleanup(-1, "Malloc failed at init_history_store");
	while (arr[++i])
		if (init_history_store_cycle(&cycle_line, arr[i]) == -1)
			break ;
	if (cycle_line)
	{
		ft_lstdel(&g_msh->history, &delete_str);
		ft_memdel((void**)&cycle_line);
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
