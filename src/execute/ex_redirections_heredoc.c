/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_redirections_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:15:19 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 20:57:44 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void		ex_rd_heredoc_getline(t_list *list, char **line)
{
	t_token		*token;

	token = list->content;
	*line = token->heredoc;
}

static void		ex_rd_heredoc_pipe(int num, char *line)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return ;
	write(fd[1], line, ft_strlen(line));
	close(fd[1]);
	dup2(fd[0], num);
	close(fd[0]);
}

static void		ex_rd_heredoc_getnum(t_list *list, int *num)
{
	t_token		*token;

	token = list->content;
	if (ft_isdigit(token->line[0]))
		*num = ft_atoi(token->line);
	else
		*num = 0;
}

void			ex_redirections_heredoc(t_list *list)
{
	t_token *token;
	char	*line;
	int		num;

	line = NULL;
	num = 0;
	while (list)
	{
		token = list->content;
		if (token->token_type == REDIRECT && token->operator_type == DLESS)
		{
			ex_rd_heredoc_getnum(list, &num);
			ex_rd_heredoc_getline(list, &line);
		}
		list = list->next;
	}
	if (line)
		ex_rd_heredoc_pipe(num, line);
	ft_memdel((void**)&line);
}
