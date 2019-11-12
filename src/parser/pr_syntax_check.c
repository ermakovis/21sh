/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:59:21 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 15:40:00 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int		pr_syntax_check_redirect(t_list *list)
{
	t_token	*token;
	int		num;

	num = 0;
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

static int		pr_syntax_check_agreg(t_list *list)
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

static int		pr_syntax_check_background(t_list *list)
{
	t_token	*token;

	token = list->content;
	if (token->operator_type != AND)
		return (SUCCESS);
	if (((t_token*)list->next->content)->token_type != NEWLINE)
	{
		ft_printf("%s: parse error near '%s'\n", g_msh->shell_name,\
				((t_token*)list->next->content)->line);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int		pr_syntax_check_operator(t_list *list)
{
	t_list	*prev;
	t_token	*curr;
	t_token	*next;

	prev = 0;
	while (list)
	{
		curr = list->content;
		if (curr->token_type == OPERATOR && curr->operator_type != AND)
		{
			next = list->next->content;
			if (curr->operator_type == SEMI && next->token_type == NEWLINE)
				return (SUCCESS);
			if (!prev || next->token_type == NEWLINE ||\
				next->token_type == OPERATOR)
			{
				ft_dprintf(2, "%s: unexpected token near '%s'\n",\
					g_msh->shell_name, curr->line);
				return (FAILURE);
			}
		}
		prev = list;
		list = list->next;
	}
	return (SUCCESS);
}

int				pr_syntax_check(t_list *list)
{
	if (pr_syntax_check_operator(list) == FAILURE)
		return (FAILURE);
	while (list)
	{
		if (pr_syntax_check_redirect(list) == FAILURE)
			return (FAILURE);
		if (pr_syntax_check_agreg(list) == FAILURE)
			return (FAILURE);
		if (pr_syntax_check_background(list) == FAILURE)
			return (FAILURE);
		list = list->next;
	}
	return (SUCCESS);
}
