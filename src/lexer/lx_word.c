/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:57:19 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 18:57:21 by tcase            ###   ########.fr       */
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
	if (ft_isprint(ch) && !ft_isspace(ch) && ch != '|' && ch != ';')
		return (1);
	return (0);
}

/*
** if starts with digits and starts
*/

int				lx_word_get(char *line)
{
	int		len;
	int		digit_check;

	len = 0;
	digit_check = 1;
	while (line[len] && lx_word_check(line[len]))
	{
		if (lx_redirect_check(line[len]) && digit_check)
			return (lx_redirect_get(line));
		if (!ft_isdigit(line[len]))
			digit_check = 0;
		if (line[len] == '\\')
			len++;
		else if (line[len] == '\'')
			len += ft_strclen(&line[len + 1], "'\'") + 1;
		else if (line[len] == '\"')
			len += lx_word_dquote_len(&line[len]);
		else
			len++;
	}
	add_token(line, len, WORD, NONE);
	return (len);
}
