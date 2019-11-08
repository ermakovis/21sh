/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 18:58:12 by tcase             #+#    #+#             */
/*   Updated: 2019/08/25 14:28:05 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void		cl_history(void)
{
	char	*path;
	int		fd;
	t_list	*list;

	if (!init_history_getpath(&path))
		return ;
	if ((fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
	{
		ft_dprintf(STDERR_FILENO, "42sh: can't open history's file\n");
		ft_memdel((void**)&path);
		return ;
	}
	list = g_msh->history;
	while (list)
	{
		ft_dprintf(fd, "%s\n", list->content);
		list = list->next;
	}
	ft_memdel((void**)&path);
	ft_lstdel(&g_msh->history, &delete_str);
	close(fd);
}

static void	cl_term_cmd_struct(void)
{
	t_cmd	*cmd;

	if (!g_msh->cmd)
		return ;
	cmd = g_msh->cmd;
	ft_memdel((void**)&cmd->area);
	ft_memdel((void**)&g_msh->cmd);
}

void		cl_rl_struct(void)
{
	if (!g_msh->rl)
		return ;
	ft_memdel((void**)&g_msh->rl->line);
	ft_memdel((void**)&g_msh->rl->history_orig);
	ft_memdel((void**)&g_msh->rl->search_line);
	ft_memdel((void**)&g_msh->rl);
}

void		cleanup(int exit_code, char *message)
{
	if (message)
		ft_dprintf(2, "%s\n", message);
	if (!g_msh)
		exit(exit_code);
	if (g_msh->original_state)
		set_terminal_canon();
	cl_rl_struct();
	cl_history();
	cl_term_cmd_struct();
	pr_ast_del(&g_msh->ast);
	ft_lstdel(&g_msh->env, &delete_var);
	ft_lstdel(&g_msh->var, &delete_var);
	ft_lstdel(&g_msh->cmd_var, &delete_var);
	ft_lstdel(&g_msh->hash, &del_hash);
	ft_lstdel(&g_msh->alias, &delete_var);
	ft_lstdel(&g_msh->bin, &delete_builtins);
	ft_lstdel(&g_msh->tokens, &del_token);
	ft_lstdel(&g_msh->jobs, &del_job);
	ft_memdel((void**)&g_msh->copy_buffer);
	ft_memdel((void**)&g_msh->shell_name);
	ft_memdel((void**)&g_msh->original_state);
	ft_memdel((void**)&g_msh);
	exit(exit_code);
}
