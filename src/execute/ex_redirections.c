/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:09:33 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 19:25:56 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int		ex_redirections(t_list *list)
{
	t_token		*token;
	int			otype;

	ex_redirections_heredoc(list);
	while (list)
	{
		token = list->content;
		otype = token->operator_type;
		if (token->token_type == REDIRECT)
		{
			if (otype == LESS || otype == MORE || otype == DMORE)
			{
				if (ex_redirections_simple(list) == BIN_FAILURE)
					return (BIN_FAILURE);
			}
			else if (otype == LESS_AND || otype == MORE_AND)
			{
				if (ex_redirections_agreg(list) == BIN_FAILURE)
					return (BIN_FAILURE);
			}
		}
		list = list->next;
	}
	return (BIN_SUCCESS);
}
