/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:58:06 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 15:37:13 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static bool	pr_bg_check(t_list *list)
{
	if (!list)
		return (false);
	while (list->next && ((t_token*)list->next->content)->token_type != NEWLINE)
		list = list->next;
	if (((t_token*)list->content)->operator_type == AND)
	{
		ft_lst_remove(&g_msh->tokens, list, &del_token);
		return (true);
	}
	return (false);
}

static void	pr_bg_mark(t_ast *ast)
{
	if (!ast)
		return ;
	pr_bg_mark(ast->left);
	pr_bg_mark(ast->right);
	ast->bg = 1;
}

t_ast		*parser(t_list **tokens)
{
	bool	bg;
	t_ast	*ast;

	if (!tokens && !*tokens)
		return (0);
	if (pr_syntax_check(*tokens) != SUCCESS)
		return (0);
	pr_heredoc(*tokens);
	bg = pr_bg_check(*tokens);
	ast = pr_ast_create(tokens);
	pr_ast_fillcommand(ast);
	if (bg)
		pr_bg_mark(ast);
	if (g_msh->display_flags & PARSER_V)
		pr_ast_print(ast, 0);
	return (ast);
}
