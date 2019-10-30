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

static void		ex_simple_hash(t_list *tokens)
{
	t_token *token;
	t_list	*list;
	t_hash	*hash;

	token = tokens->content;
	if (!(list = ft_lst_find(g_msh->hash, token->line, &cmp_hash)))
		return;
	hash = list->content;
	hash->hits++;
}

int				ex_simple_exec(t_ast *ast)
{
	char	**tokens;
	char	**env;
	char	*cmd;
	int		ret;

	ret = BIN_SUCCESS;
	ex_command_setpgid(ast->bg);
	ex_assignments_fork();
	if (ex_redirections(ast->token) == BIN_FAILURE)
		return (BIN_FAILURE);
	ex_env(&env);
	ex_tokens(&tokens, ast->token);
	ut_signal_child();
	if (ex_getpath(tokens[0], &cmd) == FAILURE)
		ret = BIN_FAILURE;
	else
	{
		execve(cmd, tokens, env);
		ft_dprintf(2, "%s: launch failed\n", cmd);
	}
	ft_memdel((void**)&cmd);
	ft_free_table(&env);
	ft_free_table(&tokens);
	return (ret);
}

int				ex_simple(t_ast *ast)
{
	pid_t		pid;
	int			status;
	int			ret;
	char		*cmd;

	status = SUCCESS;
	if (ex_expansions(&ast->token) == EXP_FAILURE)
		return (ex_set_return_var(EXP_FAILURE));
	ex_assignments(&ast->token);
	if (ast->token == NULL)
		return (SUCCESS);
	if ((ret = ex_builtin(ast->token)) != FAILURE)
		return (ex_set_return_var(ret));
	ex_simple_hash(ast->token);
	if ((pid = fork()) == -1)
		return (FAILURE);
	if (pid == 0)
		exit (ex_simple_exec(ast));
	status = ex_job(pid, ast);	
	ret = ex_exit_status(status);
	return (ex_set_return_var(ret));
}
