/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_simple.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:11:31 by tcase             #+#    #+#             */
/*   Updated: 2019/09/29 15:51:56 by tcase            ###   ########.fr       */
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
		return (((t_bin*)list_find->content)->func(list));
	return (FAILURE);
}

int			ex_set_return_var(int ret)
{
	char	*ret_line;

	if (!(ret_line = ft_itoa(ret)))
		cleanup(-1, "Malloc failed at ex_set_return_var");
	if (find_var(g_msh->env, "?"))
		set_var(g_msh->env, "?", ret_line);
	else
		add_var("?", ret_line, &g_msh->env);
	ft_memdel((void**)&ret_line);
	return (ret);
}

int				ex_simple(t_ast *ast)
{
	pid_t		pid;
	int			status;
	int			ret;

	status = SUCCESS;
	ex_expansions(ast->token);
	ex_assignments(&ast->token);
	if (ast->token == NULL)
		return (SUCCESS);
	if ((ret = ex_builtin(ast->token)) != FAILURE)
		return (ex_set_return_var(ret));
	if ((pid = fork()) == -1)
		return (FAILURE);
	if (pid == 0)
		exit(ex_command(ast));
	//waitpid(pid, &status, WUNTRACED);
	status = ex_job(pid, ast);	
	ret = ex_exit_status(status);
	ex_set_return_var(ret);
	return (ret);
}
