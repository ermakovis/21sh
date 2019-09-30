#include "msh.h"

int		bin_setenv(t_list *list)
{
	size_t	tokens_count;
	char	**tokens;
	int		ret;

	ret = SUCCESS;
	ex_tokens(&tokens, list);
	tokens_count = ft_table_size(tokens);
	if (tokens_count == 1)
		bin_env(list);
	else if (tokens_count > 3)
	{
		ret = 1;
		ft_dprintf(2, "setenv: Too many arguments.\n");
	}
	else if (find_var(g_msh->env, tokens[1]))
		set_var(g_msh->env, tokens[1], tokens[2]);
	else
		add_var(tokens[1], tokens[2], &(g_msh->env));
	ft_free_table(&tokens);
	return (ret);
}
int		bin_unsetenv(t_list *list)
{
	size_t	tokens_count;
	char	**tokens;
	int		ret;

	ret = SUCCESS;
	ex_tokens(&tokens, list);
	tokens_count = ft_table_size(tokens);
	if (tokens_count == 1)
	{
		ret = 1;
		ft_dprintf(2, "unsetenv: Not enough arguments.\n");
	}
	else if (tokens_count > 2)
	{
		ret = 1;
		ft_dprintf(2, "unsetenv: Too many arguments.\n");
	}
	else
		ft_lst_remove_if(&(g_msh->env), tokens[1], &cmp_var, &delete_var);
	ft_free_table(&tokens);
	return (ret);
}

int		bin_env(t_list *list)
{
	size_t	tokens_count;

	tokens_count = ft_lstsize(list);
	if (tokens_count > 1)
	{
		ft_dprintf(2, "%s: exit: Too many arguments.\n", g_msh->shell_name);
		return (ex_set_return_var(1));
	}
	ft_lstiter(g_msh->env, &print_var);
	return (ex_set_return_var(SUCCESS));
}
