/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:58:06 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 20:54:01 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int			parser(void)
{
	if (pr_syntax_check() != SUCCESS)
		return (FAILURE);
	pr_heredoc();
	g_msh->ast = pr_ast_create();
	if (g_msh->display_flags & PARSER_V)
		pr_ast_print(g_msh->ast, 0);
	return (SUCCESS);
}
