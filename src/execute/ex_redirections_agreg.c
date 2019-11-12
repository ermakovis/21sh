/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_redirections_agreg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:09:45 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 19:26:21 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int		ex_redirections_agreg_error(char *line, char *word)
{
	ft_dprintf(2, "%s: %s: %s\n", g_msh->shell_name, line, word);
	return (BIN_FAILURE);
}

static int		ex_redirections_agreg_more(char *redir, char *word)
{
	int		num;

	if (ft_isdigit(*redir))
		num = atoi(redir);
	else
		num = 1;
	if (ft_isnumber(word))
	{
		if (dup2(ft_atoi(word), num) == -1)
			return (ex_redirections_agreg_error("Bad file descriptor", word));
	}
	else if (ft_strequ(word, "-"))
	{
		if (close(num) == -1)
			return (ex_redirections_agreg_error("Bad file descriptor", word));
	}
	else
		return (ex_redirections_agreg_error("Ambigious redirect", word));
	return (BIN_SUCCESS);
}

static int		ex_redirections_agreg_less(char *redir, char *word)
{
	int		num;
	int		fd;

	if (ft_isdigit(*redir))
		num = atoi(redir);
	else
		num = 0;
	if (ft_isnumber(word))
	{
		fd = ft_atoi(word);
		if (dup2(ft_atoi(word), num) == -1)
			return (ex_redirections_agreg_error("Bad file descriptor", word));
	}
	else if (ft_strequ(word, "-"))
	{
		if (close(num) == -1)
			return (ex_redirections_agreg_error("Bad file descriptor", word));
	}
	else
		return (ex_redirections_agreg_error("Ambigious redirect", word));
	return (BIN_SUCCESS);
}

int				ex_redirections_agreg(t_list *list)
{
	t_token		*token;
	char		*word;

	token = list->content;
	word = ((t_token*)list->next->content)->line;
	if (token->operator_type == MORE_AND)
	{
		if (ex_redirections_agreg_more(token->line, word) == BIN_FAILURE)
			return (BIN_FAILURE);
	}
	else if (token->operator_type == LESS_AND)
	{
		if (ex_redirections_agreg_less(token->line, word) == BIN_FAILURE)
			return (BIN_FAILURE);
	}
	return (BIN_SUCCESS);
}
