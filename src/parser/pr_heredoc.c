/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_read_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 20:41:35 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 20:56:05 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char *pr_heredoc_read(t_list *list)
{
	char	*line;
	char	*tmp;
	char	*word;
	char	*rl_line;
	size_t	line_len;

	line = NULL;
	cl_rl_struct();
	word = ((t_token*)list->next->content)->line;
	while (read_line())
	{
		rl_line = g_msh->rl->line;
		line_len = ft_strlen(rl_line);
		rl_line[line_len - 1] = 0;
		if (ft_strequ(rl_line, word))
			break ;
		rl_line[line_len - 1] = '\n';
		tmp = line;
		if (!(line = ft_strjoin(line, rl_line)))
			cleanup(-1, "Malloc failed at heredoc_getline");
		ft_memdel((void**)&tmp);
		cl_rl_struct();
	}
	return (line);
}

void	pr_heredoc(void)
{
	t_list		*list;
	t_token		*token;

	list = g_msh->tokens;
	while (list)
	{
		token = list->content;
		if (token->token_type == REDIRECT && token->operator_type == DLESS)
			token->heredoc = pr_heredoc_read(list);
		list = list->next;
	}
}
