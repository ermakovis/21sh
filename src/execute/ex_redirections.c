/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:09:33 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 19:09:34 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void		ex_redirections(t_list *list)
{
	t_token		*token;

	ex_redirections_heredoc(list);
	while (list)
	{
		token = list->content;
		if (token->token_type == REDIRECT)
		{
			if (token->operator_type == LESS || token->operator_type == MORE\
				|| token->operator_type == DMORE)
				ex_redirections_simple(list);
			else if (token->operator_type == LESS_AND\
				|| token->operator_type == MORE_AND)
				ex_redirections_agreg(list);
		}
		list = list->next;
	}
}
