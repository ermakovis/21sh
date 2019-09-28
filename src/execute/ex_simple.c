/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_simple.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:11:31 by tcase             #+#    #+#             */
/*   Updated: 2019/09/28 21:52:46 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int				ex_exit_status(int status)
{
	char	*name;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		name = g_msh->shell_name;
		if (WTERMSIG(status) == 6)
			ft_dprintf(2, "%s: Abort :(\n", name);
		else if (WTERMSIG(status) == 8)
			ft_dprintf(2, "%s: Floating point exeption :(\n", name);
		else if (WTERMSIG(status) == 10)
			ft_dprintf(2, "%s: Bus error :(\n", name);
		else if (WTERMSIG(status) == 11)
			ft_dprintf(2, "%s: Segmentation Fault :(\n", name);
		return (WTERMSIG(status) * -1);
	}
	else
		return (FAILURE);
}

static int		ex_builtin(t_list *list)
{
	t_list	*list_find;
	t_token	*token;

	token = list->content;
	if ((list_find = ft_lst_find(g_msh->bin, token->line, &cmp_bins)))
	{
		((t_bin*)list_find->content)->func(list);
		return (SUCCESS);
	}
	return (FAILURE);
}

int				ex_simple(t_ast *ast)
{
	pid_t		pid;
	int			status;

	status = SUCCESS;
	ex_assignments(&ast->token);
	if (ast->token == NULL)
		return (SUCCESS);
	if (ex_builtin(ast->token) == SUCCESS)
		return (SUCCESS);
	if ((pid = fork()) == -1)
		return (FAILURE);
	if (pid == 0)
		exit(ex_command(ast));
	//waitpid(pid, &status, WUNTRACED);
	status = ex_job(pid, ast);	
	return (ex_exit_status(status));
}
