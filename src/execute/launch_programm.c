/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_programm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:16:34 by tcase             #+#    #+#             */
/*   Updated: 2019/07/26 19:18:09 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	lch_create_list(void)
{
	char	**env;
	char	**tokens;
	char	separator;
	int		*fd;

	if (!(fd = (int*)malloc(sizeof(int) * 3)))
		cleanup(-1, "Malloc failed at create_list");
	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	while (g_msh->tok && g_msh->tok->content)
	{
		lch_check_var();
		find_executable();
		lch_env(&env);
		separator = lch_tokens(&tokens, &fd);
		add_lch(env, tokens, separator, fd);
	}
}

void		lch_launch_dups(t_list *list)
{
	t_lch	*lch;

	lch = list->content;
	if (lch->fd[0] != -1)
		dup2(lch->fd[0], STDIN_FILENO);
	if (lch->fd[1] != -1)
		dup2(lch->fd[1], STDOUT_FILENO);
	if (lch->fd[2] != -1)
		dup2(lch->fd[2], STDERR_FILENO);
}

void		lch_launch_closes(void)
{
	t_list	*list;
	t_lch	*lch;

	list = g_msh->lch;
	while (list) 
	{
		lch = list->content;
		if (lch->fd[0] != -1)
			close (lch->fd[0]);
		if (lch->fd[1] != -1)
			close (lch->fd[1]);
		if (lch->fd[2] != -1)
			close (lch->fd[2]);
		if (lch->separator != '|')
			return ;
		list = list->next;
	}
}

void lch_create_pipes(void)
{
	t_list	*list;
	t_lch	*lch;
	int		fd[2];

	list = g_msh->lch;
	while (list)
	{
		lch = list->content;
		if (lch->separator != '|')
			return ;
		if (pipe(fd) == -1)
			cleanup(-1, "Failed to create a pipe");
		lch->fd[1] = fd[1];
		list = list->next;
		lch = list->content;
		lch->fd[0] = fd[0];
	}
}

void		launch_program(void)
{
	if (!g_msh->tok || !g_msh->tok->content)
		return ;
	lch_create_list();
	lch_launch();
	ft_lstdel(&g_msh->lch, &del_lch);
}
