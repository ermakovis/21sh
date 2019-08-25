/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 11:14:35 by tcase             #+#    #+#             */
/*   Updated: 2019/08/25 16:04:16 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int			ex_semi(t_ast *ast)
{
	execute(ast->left);
	return (execute(ast->right));
}

int			ex_orif(t_ast *ast)
{
	if (execute(ast->left) == SUCCESS)
		return (SUCCESS);
	return (execute(ast->right));
}

int			ex_andif(t_ast *ast)
{
	if (execute(ast->left) != SUCCESS)
		return (FAILURE);
	return (execute(ast->right));
}

int			execute(t_ast *ast)
{
	if (!ast)
		return (SUCCESS);
	if (ast->operator_type == SEMI)
		return (ex_semi(ast));
	else if (ast->operator_type == PIPE)
		return (ex_pipe(ast));
	else if (ast->operator_type == OR_IF)
		return (ex_orif(ast));
	else if (ast->operator_type == AND_IF)
		return (ex_andif(ast));
	else if (ast->node_type != OPERATOR)
		return (ex_simple(ast));
	return (SUCCESS);
}
