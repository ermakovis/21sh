/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:59:21 by tcase             #+#    #+#             */
/*   Updated: 2019/09/29 13:57:05 by tcase            ###   ########.fr       */
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
	if (ft_isnumber(token->line) && (num = ft_atoi(token->line)) > 2)
	{
		ft_printf("%s: %d: bad file descriptor\n", g_msh->shell_name, num);
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

static int	pr_syntax_check_background(t_list *list)
{
	t_token	*token;

	token = list->content;
	if (token->operator_type != AND)
		return (SUCCESS);
	if (list->next != 0 && ((t_token*)list->next->content)->token_type != NEWLINE)
	{
		ft_printf("%s: parse error near '%s'\n", g_msh->shell_name,\
				((t_token*)list->next->content)->line);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	pr_syntax_check_pipe(t_list *list)
{
	t_list	*prev;
	int		op_type;

	prev = 0;
	while(list)
	{
		op_type = ((t_token*)list->content)->operator_type;
		if (op_type == PIPE && (!prev || !list->next))
		{
			ft_printf("%s: unexpected token near `|'\n", g_msh->shell_name);
			return (FAILURE);
		}
		if (op_type == PIPE && list->next)
		{
			op_type = ((t_token*)list->next->content)->operator_type;
			if (op_type == SEMI || op_type == AND_IF ||\
				op_type == OR_IF || op_type == PIPE)
			{
				ft_printf("%s: unexpected token near `|'\n", g_msh->shell_name);
				return (FAILURE);
			}
		}
		prev = list;
		list = list->next;
	}
	return (SUCCESS);
}

int			pr_syntax_check(void)
{
	t_list	*list;

	list = g_msh->tokens;
	if (pr_syntax_check_pipe(list) == FAILURE)
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
