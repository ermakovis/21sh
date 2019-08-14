#include "msh.h"

int		ex_check_executable(char *path)
{
	if (!(ft_test_path(path) & 1))
	{
		ft_dprintf(2, "%s: permission denied\n", path);
		return (FAILURE);
	}
	return (SUCCESS);
}

static char	*eg_exec_join(char *s1, char *s2)
{
	char	*join;
	int		s1len;
	int		s2len;

	if (!s1 && !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(join = ft_strnew(s1len + s2len + 1)))
		return (NULL);
	ft_memcpy(join, s1, s1len);
	if (*(join + s1len) != '/')
		ft_memset(join + s1len, '/', 1);
	ft_memcpy(join + s1len + 1, s2, s2len);
	return (join);
}

static void	eg_get_full_path(char *path, char *token, char **cmd)
{
	if (ft_strnequ(token, path, ft_strlen(path)))
		*cmd = ft_strdup(token);
	else
		*cmd = eg_exec_join(path, token);
}

int			ex_getpath(char *token, char **cmd)
{
	int		i;
	char	**paths;
	char	*paths_env;

	if (!token || !*token)
		return (FAILURE);
	if (!(paths_env = find_var(g_msh->env, "PATH")))
		return (FAILURE);
	i = -1;
	if (!(paths = ft_strsplit(paths_env, ':')))
		cleanup(-1, "Malloc failed at ex_command_getpath");
	while (paths[++i])
	{
		eg_get_full_path(paths[i], token, cmd);
		if (ft_test_path(*cmd))
			break ;
		else
			ft_memdel((void**)cmd);
	}
	ft_free_table(&paths);
	if (*cmd == NULL)
	{
		ft_dprintf(2, "%s: command not found\n", token);
		return (FAILURE);
	}
	return (SUCCESS);
}
