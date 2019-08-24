/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_tokens_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:17:46 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 19:17:49 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	ex_tokens_quotes_bslash(char **line, int *i, char **token)
{
	(*line)++;
	realloc_check(token, *i);
	if (**line != '\n')
		*token[(*i)++] = **line;
}

static void	ex_tokens_quotes_single(char **line, int *i, char **token)
{
	(*line)++;
	while (**line && **line != '\'')
	{
		realloc_check(token, *i);
		(*token)[(*i)++] = **line;
		(*line)++;
	}
}

static void	ex_tokens_quotes_double(char **line, int *i, char **token)
{
	(*line)++;
	while (**line && **line != '\"')
	{
		realloc_check(token, *i);
		if (**line == '$')
			ex_tokens_expans_dsign(line, i, token);
		else if (**line == '\\')
			ex_tokens_quotes_bslash(line, i, token);
		else
			(*token)[(*i)++] = **line;
		(*line)++;
	}
}

void		ex_tokens_quotes(char **line, int *i, char **token)
{
	if (**line == '\'')
		ex_tokens_quotes_single(line, i, token);
	else if (**line == '\"')
		ex_tokens_quotes_double(line, i, token);
	else if (**line == '\\')
		ex_tokens_quotes_bslash(line, i, token);
}
