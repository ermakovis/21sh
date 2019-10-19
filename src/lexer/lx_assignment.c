/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_assignment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:55:13 by tcase             #+#    #+#             */
/*   Updated: 2019/08/25 15:09:13 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int			lx_assignment_check(char *line, t_list *list)
{
	t_list	*prev;
	int		len;
	int		eq_pos;

	len = 0;
	if (ft_isdigit(line[len]))
		return (0);
	while (list && list->next)
		list = list->next;
	if (!(!list || ((t_token*)list->content)->token_type == ASSIGNMENT ||\
		((t_token*)list->content)->token_type == OPERATOR))
		return (0);
	while (line[len] && ft_isprint(line[len]) && !ft_isspace(line[len]))
		len++;
	eq_pos = ft_strclen(line, "=");
	if (eq_pos && len >= eq_pos)
		return (1);
	return (0);
}

static int		lx_assignment_dquote_len(char *line)
{
	int		len;

	len = 1;
	while (line[len] && line[len] != '\"')
	{
		if (line[len] == '\\')
			len++;
		len++;
	}
	return (len + 1);
}

int			lx_assignment_get(char *line, t_list **tokens)
{
	int		len;
	char	*token_line;

	len = 0;
	while (line[len] && lx_word_check(line[len])) 
	{
		if (line[len] == '\\')
			len++;
		else if (line[len] == '\'')
			len += ft_strclen(&line[len + 1], "'\'") + 1;
		else if (line[len] == '\"')
			len += lx_assignment_dquote_len(&line[len]);
		else
			len++;
	}
	return (add_token(tokens, lx_line(line, len), ASSIGNMENT, NONE));
}
