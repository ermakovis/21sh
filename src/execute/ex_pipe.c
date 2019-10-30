/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:18:19 by tcase             #+#    #+#             */
/*   Updated: 2019/09/29 15:51:57 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int				ex_pipe_exec(t_ast *ast)
{
	char	**tokens;
	char	**env;
	char	*cmd;
	int		ret;

	cmd = NULL;
	ex_command_setpgid(ast->bg);
	ex_assignments(&ast->token);
	ex_assignments_fork();
	if (ex_expansions(&ast->token) == EXP_FAILURE)
		return (EXP_FAILURE);
	if (ex_redirections(ast->token) == BIN_FAILURE)
		return (BIN_FAILURE);
	if ((ret = ex_builtin(ast->token)) != FAILURE)
		return (BIN_FAILURE);
	ex_env(&env);
	ex_tokens(&tokens, ast->token);
	ut_signal_child();
	if (ex_getpath(tokens[0], &cmd) == FAILURE)
		ret = FAILURE;
	else if ((ret = execve(cmd, tokens, env) == -1))
		ft_dprintf(2, "%s: launch failed\n", cmd);
	ft_memdel((void**)&cmd);
	ft_free_table(&env);
	ft_free_table(&tokens);
	return (ret);
}

static int		ex_pipe_right(t_ast *ast, int fd[2])
{
	pid_t	pid;
	int		status;
	int		ret;

	if ((pid = fork()) == -1)
		cleanup(-1, "Fork failed at ex_pipe_right");
	if (pid == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (FAILURE);
		close(fd[1]);
		if (ast->parent->parent && ast->parent->parent->operator_type == PIPE)
			exit(ex_pipe_switch(ast, ast->parent->parent->right));
		else
			exit(ex_pipe_exec(ast));
	}
	close(fd[1]);
	status = ex_job(pid, ast);	
	ret = ex_exit_status(status);
	ex_set_return_var(ret);
	return (ex_exit_status(status));
}

int				ex_pipe_switch(t_ast *left, t_ast *right)
{
	pid_t	pid;
	int		fd[2];
	int		status_right;

	if (pipe(fd) == -1)
		return (FAILURE);
	if ((pid = fork()) == -1)
		cleanup(-1, "Fork failed at ex_pipe");
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (FAILURE);
		exit(ex_pipe_exec(left));
	}
	status_right = ex_pipe_right(right, fd);
	close(fd[0]);
	waitpid(pid, NULL, 0);
	return (status_right);
}

int				ex_pipe(t_ast *ast)
{
	if (!ast->left)
		return (ex_pipe_switch(ast, ast->parent->right));
	else
		return (ex_pipe(ast->left));
}
