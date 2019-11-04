#include "msh.h"

static void	bin_fc_execute(t_list *list)
{
	t_list	*tokens;
	t_ast	*ast;
	char	*tmp;

	while (list)
	{
		ft_printf("> %s\n", list->content);
		tmp = list->content;
		list->content = ft_strjoin(list->content, "\n");
		ft_memdel((void**)&tmp);	
		tokens = lexer(list->content);
		ast = parser(&tokens);
		execute(ast);
		ft_lstdel(&tokens, &del_token);
		pr_ast_del(&ast);
		list = list->next;
	}
	return ;
}

void	bin_fc_edit(t_list *list)
{
	return ;
}

void	bin_fc_print(t_list *list, int flags)
{
	while (list)
	{
		if (flags & BIN_FC_LIST_NONUM)
			ft_printf("\t%s\n", list->content);
		else
			ft_printf("%d\t%s\n", list->content_size, list->content);
		list = list->next;
	}
}

void	bin_fc_switch(t_list **history, int flags)
{
	if (flags & BIN_FC_REV)
		ft_lstrev(history);
	if (!(flags & BIN_FC_NOEDIT) && (!(flags & BIN_FC_LIST)))
		bin_fc_edit(*history);
	if (flags & BIN_FC_LIST)
		bin_fc_print(*history, flags);
	if (!(flags & BIN_FC_LIST))
		bin_fc_execute(*history);
}

int		bin_fc(t_list *list)
{
	int		flags;
	char	**tokens;
	char	*editor;
	t_list	*history;

	ft_lstpop(&g_msh->history, &delete_str);
	if (!g_msh->history)
		return (bin_print_error("history is empty", "fc", 0));
	ex_tokens(&tokens, list);
	if (bin_fc_parse(tokens, &editor, &flags) == -1)
		return (bin_print_error("usage: fc [-e name] [-lnr] [first] [last]",\
			"fc", &tokens));	
	if (bin_fc_list(tokens, &history, flags) == -1)
		return (bin_print_error("history specification out of range",\
			"fc", &tokens));
	bin_fc_switch(&history, flags);
	ft_lstdel(&history, &delete_str);
	ft_free_table(&tokens);
	ft_memdel((void**)&editor);
	return (BIN_SUCCESS);
}
