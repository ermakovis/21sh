/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:59:21 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 18:59:44 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int			pr_syntax_check_redirect(t_list *list)
{
	t_token	*token;

	token = list->content;
	if (token->token_type != REDIRECT)
		return (SUCCESS);
	token = list->next->content;
	if (token->token_type != WORD)
	{
		ft_printf("%s: syntax error near unexpected token `%s'\n",\
			g_msh->shell_name, token->line);
		return (FAILURE);
	}
	return (SUCCESS);
}

int			pr_syntax_check_agreg(t_list *list)
{
	t_token	*token;
	char	*word;

	token = list->content;
	if (token->token_type != REDIRECT)
		return (SUCCESS);
	if (!(token->operator_type == LESS_AND || token->operator_type == MORE_AND))
		return (SUCCESS);
	token = list->next->content;
	word = token->line;
	if (!ft_isnumber(word) && !ft_strequ(word, "-"))
	{
		ft_printf("%s: %s: ambigious redirect\n",\
			g_msh->shell_name, token->line);
		return (FAILURE);
	}
	return (SUCCESS);
}

int			pr_syntax_check(void)
{
	t_list	*list;

	list = g_msh->tokens;
	while (list)
	{
		if (pr_syntax_check_redirect(list) == FAILURE)
			return (FAILURE);
		if (pr_syntax_check_agreg(list) == FAILURE)
			return (FAILURE);
		list = list->next;
	}
	return (SUCCESS);
}
