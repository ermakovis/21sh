#include "msh.h"

void	ex_env(char ***env)
{
	t_list	*env_list;
	char	**ret;
	size_t	size;
	int		i;

	i = 0;
	if (!(env_list = g_msh->env))
		return ;
	size = ft_lstsize(env_list) + 1;
	if (!(ret = (char**)malloc(sizeof(char*) * size)))
		cleanup(-1, "Malloc failed at ex_command_env");
	ft_bzero(ret, sizeof(char*) * size);
	while (env_list)
	{
		ret[i++] = var_to_str(env_list->content);
		env_list = env_list->next;
	}
	*env = ret;
}

int ex_builtin(char **tokens)
{
	return (FAILURE);
}


int			ex_command(t_ast *ast)
{
	char	**env;
	char	**tokens;
	char	*cmd;
	int		ret;

	env = NULL;
	tokens = NULL;
	ex_env(&env); 
	ex_tokens(ast, &tokens);
	if (ex_builtin(tokens))
		ret = SUCCESS;
	else if ((ret = ex_getpath(tokens[0], &cmd) == SUCCESS))
		ret = ex_command_fork(cmd, tokens, env);
	ft_free_table(&env);
	ft_free_table(&tokens);
	return (ret);
}
