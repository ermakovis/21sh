#include "msh.h"

static void	bin_fc_edit_create(t_list *list, char **name)
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
	while(list)
	{
		ft_dprintf(fd, "%s\n", list->content);
		list = list->next;
	}
}

static void	bin_fc_edit_action(char *name, char *editor)
{
	t_list	*tokens;
	t_ast	*ast;
	char	*line;

	if (!(line = ft_powerjoin("%s %s\n", editor, name)))
		cleanup(-1, "Malloc failed at bin_fc_action");
	tokens = lexer(line);
	ft_memdel((void**)&line);
	ast = parser(&tokens);
	execute(ast);
	ft_lstdel(&tokens, &del_token);
	pr_ast_del(&ast);
	return ;
}

static void	bin_fc_edit_read(char *file_name, char **file_content)
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
	close(fd);
}

static void	bin_fc_edit_process(t_list **list, char *file_content)
{
	char	**table;
	char	*line;
	int		i;
	int		ret;

	i = -1;
	line = 0;
	ft_lstdel(list, &delete_str);
	if (!(table = ft_strsplit(file_content, '\n')))
		cleanup(-1, "Malloc failed at bin_fc_edit_process");
	while (table[++i])
	{
		if (line && !(line = ft_powerjoin("%f\n%s", &line, table[i])))
			cleanup(-1, "Malloc failed at bin_fc_edit_process");
		if (!line && !(line = ft_powerjoin("%f%s", &line, table[i])))
			cleanup(-1, "Malloc failed at bin_fc_edit_process");
		if ((ret = init_history_store_valid(line)) == 0)
		{
			add_str(list, line);
			ft_memdel((void**)&line);
		}
		else if (ret == 2)
		{
			ft_lstdel(list, &delete_str);
			break ;
		}
	}
	if (line)
	{
		ft_dprintf(2, "%s: fc: failed to process input\n", g_msh->shell_name);
		ft_memdel((void**)&line);
		ft_lstdel(list, &delete_str);
	}
	ft_free_table(&table);	
}

int			bin_fc_edit(t_list **list, char *editor)
{
	char	*file_name;
	char	*file_content;

	bin_fc_edit_create(*list, &file_name);
	bin_fc_edit_action(file_name, editor);
	bin_fc_edit_read(file_name, &file_content);
	bin_fc_edit_process(list, file_content);
	if (remove(file_name) == -1)
		bin_print_error("failed to delete file", "fc", 0);
	ft_memdel((void**)&file_name);
	ft_memdel((void**)&file_content);
	return (BIN_SUCCESS);
}
