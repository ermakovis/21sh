/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_ast_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:58:41 by tcase             #+#    #+#             */
/*   Updated: 2019/08/25 13:43:28 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
**	t_ast left and right techincally incorrect but i like them that way
*/

static t_ast	*pr_ast_create_pipe(void)
{
	t_ast	*root;
	t_ast	*left;
	t_ast	*right;

	root = pr_ast_create_leaf(OPERATOR);
	while (((t_token*)g_msh->tokens->content)->operator_type == PIPE)
	{
		left = pr_ast_create_leaf(WORD);
		right = pr_ast_create_leaf(OPERATOR);
		root = pr_ast_create_node(left, root, right);
	}
	return (root);
}

static t_ast	*pr_ast_create_andor(void)
{
	t_ast	*root;
	t_ast	*left;
	t_ast	*right;

	root = pr_ast_create_pipe();
	while (((t_token*)g_msh->tokens->content)->operator_type == OR_IF\
			|| ((t_token*)g_msh->tokens->content)->operator_type == AND_IF)
	{
		left = pr_ast_create_leaf(WORD);
		right = pr_ast_create_pipe();
		root = pr_ast_create_node(left, root, right);
	}
	return (root);
}

t_ast			*pr_ast_create(void)
{
	t_ast	*root;
	t_ast	*left;
	t_ast	*right;

	root = pr_ast_create_andor();
	while (((t_token*)g_msh->tokens->content)->operator_type == SEMI)
	{
		left = pr_ast_create_leaf(WORD);
		right = pr_ast_create_andor();
		root = pr_ast_create_node(left, root, right);
	}
	return (root);
}
