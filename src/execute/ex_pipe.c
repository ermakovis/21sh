#include "msh.h"

//static int	ex_pipe_edge(t_ast *ast)
//{
//	char	**tokens;
//	char	**env;
//	char	*cmd;
//	int		ret;
//
//	cmd = NULL;
//	ret = SUCCESS;
//	ex_redirections(ast->token);
//	ex_tokens_assignments(&ast->token);
//	if (ast->token == NULL)
//		return (SUCCESS);
//	ex_env(&env);
//	ex_tokens(ast, &tokens);
//	if (ex_builtin(tokens) == SUCCESS)
//		ret = SUCCESS;
//	else if (ex_getpath(tokens[0], &cmd) == FAILURE)
//		ret = FAILURE;
//	else if (ex_check_executable(cmd) == FAILURE)
//		ret = FAILURE;
//	else if ((ret = execve(cmd, tokens, env) == -1))
//		ft_dprintf(2, "%s: launch failed\n", cmd);
//	ft_memdel((void**)&cmd);
//	ft_free_table(&env);
//	ft_free_table(&tokens);
//	return (ret);
//}

static int			ex_pipe_right(t_ast *ast, int fd[2])
{
	pid_t	pid;
	int		status;

	if ((pid = fork()) == -1)
		cleanup(-1, "Fork failed at ex_pipe_right");
	if (pid == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (FAILURE);
		close(fd[1]);
		if (ast->parent->parent && ast->parent->parent->operator_type == PIPE)
			exit (ex_pipe_switch(ast, ast->parent->parent->right));
		else
			exit (ex_command(ast));
	}
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
	}
	return (SUCCESS);
};

int			ex_pipe_switch(t_ast *left, t_ast *right)
{
	pid_t	pid;
	int		status;
	int		fd[2];
		
	if (pipe(fd) == -1)
		return (FAILURE);
	if ((pid = fork()) == -1)
		cleanup(-1, "Fork failed at ex_pipe");
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (FAILURE);
		exit (ex_command(left));
	}
	else
	{
		ex_pipe_right(right, fd);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
	return (SUCCESS);
};

int			ex_pipe(t_ast *ast)
{
	if (!ast->left)
		return (ex_pipe_switch(ast, ast->parent->right));
	else
		return (ex_pipe(ast->left));
}

