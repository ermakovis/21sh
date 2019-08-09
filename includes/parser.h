#ifndef PARSER_H
# define PARSER_H

typedef struct		s_ast
{
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
	int				node_type;
	int				operator_type;
	t_list			*token;	
}					t_ast;

int					parser(void);

/*
**	pr_ast_functions.c
*/
t_ast		*pr_ast_create_node(t_ast *node, t_ast *left, t_ast *right);
t_ast		*pr_ast_create_leaf(int delim);
void		pr_ast_print(t_ast *ast, int lvl);
void		pr_ast_del(t_ast **ast);

/*
**	pr_ast_create.c
**	--pr_ast_create_pipe(void);
*/
t_ast		*pr_ast_create(void);



#endif
