/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_expansions_remquotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:47:55 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 20:08:31 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	ex_expansions_remquotes_cycle(char *line, int *i,\
		int *squote, int *dquote)
{
	if (line[*i] == '\\' && !squote)
	{
		ft_memmove(&line[*i], &line[*i + 1], ft_strlen(&line[*i]));
		(*i)++;
	}
	else if (line[*i] == '\'' && !*dquote)
	{
		ft_memmove(&line[*i], &line[*i + 1], ft_strlen(&line[*i]));
		*squote ^= 1;
	}
	else if (line[*i] == '\"' && !*squote)
	{
		ft_memmove(&line[*i], &line[*i + 1], ft_strlen(&line[*i]));
		*dquote ^= 1;
	}
	else
		(*i)++;
}

void		ex_expansions_remquotes(t_token *token)
{
	int		i;
	int		squote;
	int		dquote;
	char	*line;

	i = -1;
	squote = 0;
	dquote = 0;
	line = token->line;
	while (line[++i])
		ex_expansions_remquotes_cycle(line, &i, &squote, &dquote);
}
