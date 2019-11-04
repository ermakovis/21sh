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
	char 	*tmp;

	if (!(line = ft_strjoin(editor, " ")))
		cleanup(-1, "Malloc failed at bin_fc_edit_action");
	tmp = line;
	if (!(line = ft_strjoin(line, name)))
		cleanup(-1, "Malloc failed at bin_fc_edit_action");
	ft_memdel((void**)&tmp);
	tmp = line;
	if (!(line = ft_strjoin(line, "\n")))
		cleanup(-1, "Malloc failed at bin_fc_edit_action");
	ft_memdel((void**)&tmp);
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
	char	*curline;
	char	*tmp;
	int		i;

	i = -1;
	curline = 0;
	ft_lstdel(list, &delete_str);
	if (!(table = ft_strsplit(file_content, '\n')))
		cleanup(-1, "Malloc failed at bin_fc_edit_process");
	while (table[++i])
	{
		tmp = curline;
		if (!(curline = ft_strjoin(curline, table[i])))
			cleanup(-1, "Malloc failed at bin_fc_edit_process");
		ft_memdel((void**)&tmp);
		if (rl_newline_check(curline, RL_MODE) == 0)
		{
			add_str(list, curline);
			ft_memdel((void**)&curline);
		}
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
