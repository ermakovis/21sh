/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:54:51 by tcase             #+#    #+#             */
/*   Updated: 2019/09/29 14:30:12 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int		lx_newline(t_list **tokens)
{
	add_token(tokens, lx_line("<newline>", 9), NEWLINE, NONE);
	return (1);
}

static void		lx_print(t_list *tokens)
{
	ft_printf("---LEXER---\n");
	ft_lstiter(tokens, &print_token);
	ft_printf("-----------\n\n");
}

char			*lx_line(char *line, int len)
{
	char	*ret;

	if (len == 0)
	{
		if (!(ret = ft_strdup(line)))
			cleanup(-1, "Malloc failed at lx_line");
	}
	else if (!(ret = ft_strndup(line, len)))
		cleanup(-1, "Malloc failed at lx_line");
	return (ret);
}

t_list			*lx_tokens(char *line)
{
	t_list		*tokens;

	if (!line || !*line)
		return (0);
	tokens = 0;
	while (*line)
	{
		if (lx_assignment_check(line, tokens))
			line += lx_assignment_get(line, &tokens);
		else if (lx_operator_check(*line))
			line += lx_operator_get(line, &tokens);
		else if (lx_redirect_check(*line))
			line += lx_redirect_get(line, &tokens);
		else if (lx_word_check(*line))
			line += lx_word_get(line, &tokens);
		else if (*line == '\n')
			line += lx_newline(&tokens);
		else
			line++;
	}
	if (g_msh->display_flags & LEXER_V)
		lx_print(tokens);
	return (tokens);
}

t_list			*lexer(char *line)
{
	t_list	*ret_list;
	
	ret_list = lx_tokens(line);
	lx_alias(&ret_list);
	return(ret_list);
}
