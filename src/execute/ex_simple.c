#include "msh.h"

static int ex_builtin(t_list *list)
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
	
	ex_assignments(&ast->token);
	if (ast->token == NULL)
		return (SUCCESS);
	if (ex_builtin(ast->token) == SUCCESS)
		return (SUCCESS);
	if ((pid = fork()) == -1)
		return (FAILURE);
	if (pid == 0)
		exit (ex_command(ast));
	waitpid(pid, &status, 0);
	return (SUCCESS);
}
