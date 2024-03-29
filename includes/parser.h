/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:25:49 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 20:52:05 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct		s_ast
{
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
	int				node_type;
	int				operator_type;
	bool			bg;
	int				*fd;
	t_list			*token;
}					t_ast;

/*
**	parser.c
*/
t_ast				*parser(t_list **tokens);

/*
**	pr_heredoc.c
*/
void				pr_heredoc(t_list *tokens);

/*
**	pr_syntax_check.c
**	--pr_syntax_check_redirect(t_list *list)
*/
int					pr_syntax_check(t_list *tokens);

/*
**	pr_ast_fillcommand.c
*/
void				pr_ast_fillcommand(t_ast *ast);
/*
**	pr_ast_functions.c
*/
t_ast				*pr_ast_create_node(t_ast *node, t_ast *left, t_ast *right);
t_ast				*pr_ast_create_leaf(int delim, t_list **list);
void				pr_ast_print(t_ast *ast, int lvl);
void				pr_ast_del(t_ast **ast);

/*
**	pr_ast_create.c
**	--pr_ast_create_pipe(void);
*/
t_ast				*pr_ast_create(t_list **tokens);
#endif
