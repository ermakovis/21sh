/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_newline_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:31:24 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 15:31:25 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int		rl_quotes_check(char *line)
{
	int		i;
	int		dquote;
	int		squote;

	i = -1;
	dquote = 0;
	squote = 0;
	while (line[++i])
	{
		if (line[i] == '\\' && squote == 0 && line[i + 1])
			i++;
		else if (line[i] == '\'' && dquote == 0)
			squote ^= 1;
		else if (line[i] == '\"' && squote == 0)
			dquote ^= 1;
	}
	return (!(dquote || squote));
}

int		rl_bslash_check(char *line)
{
	int		i;
	int		is_quoted;

	i = -1;
	while (line[++i])
	{
		is_quoted = 0;
		if (line[i] == '\\')
		{
			is_quoted = 1;
			i++;
		}
		if (!line[i] && is_quoted)
			return (0);
	}
	return (1);
}

int		rl_braces_check(char *line)
{
	char	pile[1000];
	int		pile_size;
	bool	mismatch;

	pile_size = 0;
	mismatch = false;
	while (*line && mismatch == false)
	{
		if (*line == '(')
			pile[pile_size++] = ')';
		else if (*line == '[')
			pile[pile_size++] = ']';
		else if (*line == '{')
			pile[pile_size++] = '}';
		else if (*line == ')' || *line == ']' || *line == '}')
			if (pile_size == 0 || pile[--pile_size] != *line)
				mismatch = true;
		line++;
	}
	if (mismatch == true)
		return (2);
	if (pile_size > 0)
		return (1);
	return (0);
}

int		rl_newline_check(char *line, int mode)
{
	int		ret;

	if (mode == HEREDOC_MODE)
		return (0);
	if (rl_quotes_check(line) == 0)
	{
		rl_print_char('\n');
		ft_printf("> ");
		return (1);
	}
	if (rl_bslash_check(line) == 0)
	{
		rl_print_char('\n');
		ft_printf("> ");
		return (1);
	}
	if ((ret = rl_braces_check(line)))
	{
		if (ret == 2)
			ft_dprintf(2, "\n%s: braces are unbalanced\n", g_msh->shell_name);
		if (ret == 1)
			ft_printf("\n> ");
	}
	return (ret);
}
