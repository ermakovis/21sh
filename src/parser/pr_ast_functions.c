#include "msh.h"

t_ast		*pr_ast_create_node(t_ast *node, t_ast *left, t_ast *right)
{
	//ft_printf("node\n");
	//ft_lstiter(node->token, &print_token);
	//ft_printf("node\n");
	//ft_lstiter(left->token, &print_token);
	//ft_printf("node\n");
	//ft_lstiter(right->token, &print_token);
	node->right = right;
	node->left = left;
	if (left)
		left->parent = node;
	if (right)
		right->parent = node;
	return (node);
}

static void	pr_ast_create_leaf_delim(int delim)
{
	t_list		*curr;
	t_list		*prev;
	t_token		*token;

	prev = g_msh->tokens;
	curr = prev->next;
	while (curr->next)
	{
		token = curr->content;
		if (token->token_type == delim)
			break ;
		prev = curr;
		curr = curr->next;
	}
	prev->next = NULL;
	g_msh->tokens = curr;
}

t_ast		*pr_ast_create_leaf(int delim)
{
	t_ast		*new;
	size_t		size;

	if (((t_token*)g_msh->tokens->content)->token_type == NEWLINE)
		return (NULL);
	size = sizeof(t_ast);
	if (!(new = (t_ast*)malloc(size)))
		cleanup (-1, "Malloc failed at ast_create_leaf");
	ft_bzero(new, size);
	new->token=g_msh->tokens;
	new->node_type = ((t_token*)g_msh->tokens->content)->token_type;
	new->operator_type = ((t_token*)g_msh->tokens->content)->operator_type;
	pr_ast_create_leaf_delim(delim);
	//ft_printf("--LEAF-%d--\n", delim);
	//ft_lstiter(new->token, &print_token);
	//ft_printf("--------\n");
	return (new);
}

void		pr_ast_print(t_ast *ast, int lvl)
{
	t_token		*token;

	if (lvl == 0)
		ft_printf("--------AST---------\n");
	if (!ast)
		return;
	if (ast->left)
		pr_ast_print(ast->left,  ++lvl);
	else
		++lvl;
	ft_printf("%*.s*****\n%*.s", lvl * 4, " ", lvl * 4, " ");
	print_token_line(ast->token);
	ft_printf("%*.s*****\n", lvl * 4, " ");
	if (ast->right)
		pr_ast_print(ast->right, lvl--);
	else
		lvl--;
	if (lvl == 0)
		ft_printf("--------------------\n");
}

void		pr_ast_del(t_ast **ast)
{
	if (!*ast)
		return;
	pr_ast_del(&(*ast)->left);
	pr_ast_del(&(*ast)->right);
	ft_lstdel(&(*ast)->token, &del_token);
	ft_memdel((void**)ast);
}
