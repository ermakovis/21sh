/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_simple_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:00:04 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 19:19:27 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void				ex_simple_save_std(t_ast *ast)
{
	int		i;

	if (!(ast->fd = ft_memalloc(sizeof(int) * 11)))
		cleanup(-1, "Malloc failed at ex_simple_save_std");
	i = -1;
	while (++i < 10)
	{
		ast->fd[i] = fcntl(i, F_DUPFD_CLOEXEC, 10);
	}
}

void				ex_simple_restore_std(t_ast *ast)
{
	int		i;
	t_list	*list;
	t_token	*token;

	i = -1;
	while (++i < 10)
		dup2(ast->fd[i], i);
	i = -1;
	while (++i < 10)
	{
		if (ast->fd[i] != -1)
			close(ast->fd[i]);
	}
	list = ast->token;
	while (list)
	{
		token = list->content;
		if (token->fd > 0)
			close(token->fd);
		list = list->next;
	}
}
