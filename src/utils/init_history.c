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
		ft_dprintf(2, "\n%s: braces are unbalanced at line %s\n",\
			g_msh->shell_name, line);
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

int			init_history_getpath(char **path)
{
	char	*ret;

	if (!(ret = find_var(g_msh->env, "HOME")))
	{
		ft_dprintf(2, "%s: failed to get home path\n", g_msh->shell_name);
		return (0);
	}
	if (ret[ft_strlen(ret)] == '/')
		ret = ft_powerjoin("%s%s", ret, HISTORY_PATH);
	else
		ret = ft_powerjoin("%s/%s", ret, HISTORY_PATH);
	*path = ret;
	return (1);
}

void		init_history(void)
{
	int		fd;
	char	*path;
	char	buff[PATH_MAX + 1];
	char	*line;
	int		res;

	line = NULL;
	if (!init_history_getpath(&path))
		return ;
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_dprintf(2, "%s: can't open history's file\n", g_msh->shell_name);
		ft_memdel((void**)&path);
		return ;
	}
	ft_memdel((void**)&path);
	while ((res = read(fd, &buff, PATH_MAX)) > 0)
	{
		buff[res] = 0;
		line = ft_powerjoin("%f%s", &line, buff);
	}
	close(fd);
	init_history_store(line);
	ft_memdel((void**)&line);
}
