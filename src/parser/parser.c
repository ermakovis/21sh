#include "msh.h"

int			parser(void)
{
	t_ast *root;

	if (pr_syntax_check() != SUCCESS)
		return (FAILURE);
	root = pr_ast_create();
	g_msh->ast = root;
	//pr_ast_print(root, 0);	
	return (SUCCESS);
}

