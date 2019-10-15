/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:58:06 by tcase             #+#    #+#             */
/*   Updated: 2019/09/29 11:00:04 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static bool	pr_bg_check(void)
{
	t_list	*list;

	if (!(list = g_msh->tokens))
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

static void pr_bg_mark(t_ast *ast)
{
	if (!ast)
		return ;
	pr_bg_mark(ast->left);
	pr_bg_mark(ast->right);
	ast->bg = 1;
}	

int			parser(void)
{
	bool	bg;

	if (pr_syntax_check() != SUCCESS)
		return (FAILURE);
	pr_heredoc();
	bg = pr_bg_check();
	g_msh->ast = pr_ast_create();
	pr_ast_fillcommand(g_msh->ast);
	if (bg)
		pr_bg_mark(g_msh->ast);
	if (g_msh->display_flags & PARSER_V)
		pr_ast_print(g_msh->ast, 0);
	return (SUCCESS);
}
