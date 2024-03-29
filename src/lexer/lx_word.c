/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:57:19 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 15:36:28 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
**	starts at 1 to ignore the first ", returns +1 to ignore the last;
*/

static int		lx_word_dquote_len(char *line)
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

int				lx_word_check(char ch)
{
	if (ch == '|' || ch == ';' || ch == '>' || ch == '<')
		return (0);
	if (ft_isprint(ch) && !ft_isspace(ch))
		return (1);
	return (0);
}

int				lx_word_braces_len(char *line)
{
	int		pile_size;
	int		len;

	pile_size = 1;
	len = 1;
	while (line[len] && pile_size)
	{
		if (line[len] == '(' || line[len] == '[' || line[len] == '{')
			pile_size++;
		else if (line[len] == ')' || line[len] == ']' || line[len] == '}')
			pile_size--;
		len++;
	}
	return (len);
}

int				lx_word_get(char *line, t_list **tokens)
{
	int		len;
	int		digit_check;

	len = 0;
	digit_check = 1;
	while (line[len] && lx_word_check(line[len]))
	{
		if (!ft_isdigit(line[len]))
			digit_check = 0;
		if (line[len] == '\\' && line[len + 1] == '\n' && line[len + 2])
			ft_memmove(&line[len], &line[len + 2], ft_strlen(line) - len);
		else if (line[len] == '\'')
			len += ft_strclen(&line[len + 1], "'\'") + 1;
		else if (line[len] == '\"')
			len += lx_word_dquote_len(&line[len]);
		else if (line[len] == '[' || line[len] == '(' || line[len] == '{')
			len += lx_word_braces_len(&line[len]);
		else
			len++;
	}
	if (lx_redirect_check(line[len]) && digit_check)
		return (lx_redirect_get(line, tokens));
	add_token(tokens, lx_line(line, len), WORD, NONE);
	return (len);
}
