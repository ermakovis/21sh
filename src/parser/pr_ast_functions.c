/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_ast_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:59:58 by tcase             #+#    #+#             */
/*   Updated: 2019/09/29 10:55:23 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_ast		*pr_ast_create_node(t_ast *node, t_ast *left, t_ast *right)
{
	node->right = right;
	node->left = left;
	if (left)
		left->parent = node;
	if (right)
		right->parent = node;
	return (node);
}

static void	pr_ast_create_leaf_delim(int delim, t_list **tokens)
{
	t_list		*curr;
	t_list		*prev;
	t_token		*token;

	prev = *tokens;
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
	*tokens = curr;
}

t_ast		*pr_ast_create_leaf(int delim, t_list **tokens)
{
	t_ast		*new;
	t_list		*list;
	t_token		*token;
	size_t		size;

	list = *tokens;
	token = list->content;
	if (token->token_type == NEWLINE)
		return (NULL);
	size = sizeof(t_ast);
	if (!(new = (t_ast*)malloc(size)))
		cleanup(-1, "Malloc failed at ast_create_leaf");
	ft_bzero(new, size);
	new->token = list;
	new->node_type = token->token_type;
	new->operator_type = token->operator_type;
	pr_ast_create_leaf_delim(delim, tokens);
	return (new);
}

void		pr_ast_print(t_ast *ast, int lvl)
{
	if (lvl == 0)
		ft_printf("--------AST---------\n");
	if (!ast)
		return ;
	if (ast->left)
		pr_ast_print(ast->left, ++lvl);
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
		return ;
	pr_ast_del(&(*ast)->left);
	pr_ast_del(&(*ast)->right);
	ft_lstdel(&(*ast)->token, &del_token);
	ft_memdel((void**)&(*ast)->fd);
	ft_memdel((void**)ast);
}
