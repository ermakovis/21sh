/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_fc_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:46:55 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 17:19:40 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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

static int	bin_fc_edit_process_cycle(t_list **list, char **line, char *table)
{
	int		ret;

	if (*line && !(*line = ft_powerjoin("%f\n%s", line, table)))
		cleanup(-1, "Malloc failed at bin_fc_edit_process");
	if (!*line && !(*line = ft_powerjoin("%f%s", line, table)))
		cleanup(-1, "Malloc failed at bin_fc_edit_process");
	if ((ret = init_history_store_valid(*line)) == 0)
	{
		add_str(list, *line);
		ft_memdel((void**)line);
	}
	else if (ret == 2)
	{
		ft_lstdel(list, &delete_str);
		return (BIN_FAILURE);
	}
	return (BIN_SUCCESS);
}

static void	bin_fc_edit_process(t_list **list, char *file_content)
{
	char	**table;
	char	*line;
	int		i;

	if (!file_content || !*file_content)
		return ;
	i = -1;
	line = 0;
	ft_lstdel(list, &delete_str);
	if (!(table = ft_strsplit(file_content, '\n')))
		cleanup(-1, "Malloc failed at bin_fc_edit_process");
	while (table[++i])
	{
		if (bin_fc_edit_process_cycle(list, &line, table[i]) == BIN_FAILURE)
			break ;
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
