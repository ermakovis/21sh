#include "msh.h"

int			parser(void)
{
	t_ast *root;

	root = pr_ast_create();
	pr_ast_print(root, 0);	
	g_msh->ast = root;
	return (1);
}

