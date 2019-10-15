#include "msh.h"

/*
**	TODO make manual join without " "
*/
static void pr_ast_fill_join(char **line, char *join)
{
	char *tmp;

	if (!*line)
	{
		if (!(*line = ft_strdup(join)))
			cleanup(-1, "Malloc failed at pr_ast_fill_join");
		return ;
	}
	tmp = *line;
	if (!(*line = ft_strjoin(*line, " ")))
		cleanup(-1, "Malloc failed at pr_ast_fill_join");
	ft_memdel((void**)&tmp);
	tmp = *line;
	if (!(*line = ft_strjoin(*line, join)))
		cleanup(-1, "Malloc failed at pr_ast_fill_join");
	ft_memdel((void**)&tmp);
}

static void	pr_ast_fill_getcmd(t_list *list)
{
	char 	*full_command;
	t_list	*ilist;
	t_token	*token;

	ilist = list;
	full_command = 0;
	while (ilist)
	{
		token = ilist->content;
		pr_ast_fill_join(&full_command, token->line);
		ilist = ilist->next;
	}
	((t_token*)list->content)->full_command = full_command;
}

void		pr_ast_fillcommand(t_ast *ast)
{
	char	*full_command;

	if (!ast)
		return ;
	if (ast->left)
		pr_ast_fillcommand(ast->left);
	if (ast->right)
		pr_ast_fillcommand(ast->right);
	if (((t_token*)ast->token->content)->token_type == OPERATOR)
		return ;
	pr_ast_fill_getcmd(ast->token);

	
};
