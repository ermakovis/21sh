#include "msh.h"

#define BIN_FC_LIST (1)
#define BIN_FC_LIST_NONUM (1 << 1)
#define BIN_FC_REV (1 << 2)
#define BIN_FC_NOEDIT (1 << 3)

static void	bin_fc_execute(t_list *list)
{
	t_list	*tokens;
	t_ast	*ast;
	char	*tmp;

	while (list)
	{
		tmp = list->content;
		list->content = ft_strjoin(list->content, "\n");
		ft_memdel((void**)&tmp);	
		tokens = lexer(list->content);
		ast = parser(&tokens);
		execute(ast);
		list = list->next;
		ft_lstdel(&tokens, &del_token);
		pr_ast_del(&ast);
	}
	return ;
}

int		bin_fc(t_list *list)
{
	int		flags;
	char	**tokens;
	char	*editor;
	t_list	*history;
	
	ex_tokens(&tokens, list);
	if (bin_fc_parse(tokens, &editor, &flags) == -1)
		return (bin_print_error("usage: fc [-e name] [-lnr] [first] [last]",\
			"fc", &tokens));	
	if (bin_fc_list(tokens, &history) == -1)
		return (bin_print_error("history specification out of range",\
			"fc", &tokens));
	bin_fc_execute(history);
	ft_lstdel(&history, &delete_str);
	ft_free_table(&tokens);
	ft_memdel((void**)&editor);
	return (BIN_SUCCESS);
	
	

}
