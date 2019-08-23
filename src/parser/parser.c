#include "msh.h"

int			parser(void)
{
	if (pr_syntax_check() != SUCCESS)
		return (FAILURE);
	g_msh->ast = pr_ast_create();
	if (g_msh->display_flags & PARSER_V)
		pr_ast_print(g_msh->ast, 0);	
	return (SUCCESS);
}

