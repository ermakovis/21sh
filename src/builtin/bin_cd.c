#include "msh.h"

static int	bin_cd_change(char *path)
{
	char	cwd[PATH_MAX];
	int		ret;

	if (!(ret = ft_test_path(path)))
	{
		ft_dprintf(STDERR_FILENO, "cd: %s: No such file or directory\n", path);
		return (BIN_FAILURE) ;
	}
	else if (ft_item_type(path) != 2)
	{
		ft_dprintf(STDERR_FILENO, "cd: %s: Not a directory\n", path);
		return (BIN_FAILURE);
	}
	else if (!(ret & 1))
	{
		ft_dprintf(STDERR_FILENO, "cd: %s: Permission denied\n", path);
		return (BIN_FAILURE);
	}
	if (chdir(path) == -1)
		ft_dprintf(STDERR_FILENO, "cd: %s: chdir failed\n", path);
	set_var(g_msh->env, "OLDPWD", find_var(g_msh->env, "PWD"));
	set_var(g_msh->env, "PWD", getcwd(cwd, PATH_MAX));
	return (BIN_SUCCESS);
}

int			bin_cd(t_list *list)
{
	int		ret;
	int		tokens_count;
	char	**tokens;

	ret = BIN_FAILURE;
	tokens_count = ft_lstsize(list);
	ex_tokens(&tokens, list);
	if (tokens_count > 2)
		ft_dprintf(2, "cd: Too many arguments\n");
	else if (tokens_count == 1)
		ret = bin_cd_change(find_var(g_msh->env, "HOME"));
	else if (ft_strequ(tokens[1], "-"))
		ret = bin_cd_change(find_var(g_msh->env, "OLDPWD"));
	else
		ret = bin_cd_change(tokens[1]);
	ft_free_table(&tokens);
	return (ret);
}
