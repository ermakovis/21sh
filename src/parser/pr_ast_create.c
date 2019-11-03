/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_ast_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:58:41 by tcase             #+#    #+#             */
/*   Updated: 2019/08/25 16:01:51 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
**	t_ast left and right techincally incorrect but i like them that way
*/

static t_ast	*pr_ast_create_pipe(t_list **tokens)
{
	t_ast	*root;
	t_ast	*left;
	t_ast	*right;

	root = pr_ast_create_leaf(OPERATOR, tokens);
	while (((t_token*)(*tokens)->content)->operator_type == PIPE)
	{
		left = pr_ast_create_leaf(WORD, tokens);
		right = pr_ast_create_leaf(OPERATOR, tokens);
		root = pr_ast_create_node(left, root, right);
	}
	return (root);
}

static t_ast	*pr_ast_create_andor(t_list **tokens)
{
	t_ast	*root;
	t_ast	*left;
	t_ast	*right;

	root = pr_ast_create_pipe(tokens);
	while (((t_token*)(*tokens)->content)->operator_type == OR_IF\
			|| ((t_token*)(*tokens)->content)->operator_type == AND_IF)
	{
		left = pr_ast_create_leaf(WORD, tokens);
		right = pr_ast_create_pipe(tokens);
		root = pr_ast_create_node(left, root, right);
	}
	return (root);
}

t_ast			*pr_ast_create(t_list **tokens)
{
	t_ast	*root;
	t_ast	*left;
	t_ast	*right;

	root = pr_ast_create_andor(tokens);
	while (((t_token*)(*tokens)->content)->operator_type == SEMI)
	{
		left = pr_ast_create_leaf(WORD, tokens);
		right = pr_ast_create_andor(tokens);
		root = pr_ast_create_node(left, root, right);
	}
	return (root);
}
