#include "msh.h"

static void	ex_expansions_tild_split(char *line, char **left, char **right)
{
	int		slash_pos;

	line++;
	slash_pos = 0;
	*left = 0;
	*right = 0;
	while (line[slash_pos] && line[slash_pos] != '/')
		slash_pos++;
	if (slash_pos)
		if (!(*left = ft_strndup(line, slash_pos)))
			cleanup(-1, "Malloc failed at ex_expansions_tild_split");
	if (line[slash_pos])
		if (!(*right = ft_strdup(line + slash_pos)))
			cleanup(-1, "Malloc failed at ex_expansions_tild_split");
}

static int	ex_expansions_tild_swap(char **left)
{
	char		*find;
	t_passwd	*passwd;

	find = 0;
	if (!*left)
		if (!(find = find_var(g_msh->env, "HOME")))
			return (FAILURE);
	if (ft_strequ(*left, "+"))
		if (!(find = find_var(g_msh->env, "PWD")))
			return (FAILURE);
	if (ft_strequ(*left, "-"))
		if (!(find = find_var(g_msh->env, "OLDPWD")))
			return (FAILURE);
	if (!find)
	{
		if (!(passwd = getpwnam(*left)))
			return (FAILURE);
		find = passwd->pw_dir;
	}
	ft_memdel((void**)left);
	if (!(*left = ft_strdup(find)))
		cleanup(-1, "Malloc failed at ex_expansions_tild_swap");
	return (SUCCESS);
}

void		ex_expansions_tild(char **line)
{
	char	*left;
	char	*right;
	char	*new;

	if (!line || !*line || *line[0] != '~')
		return ;
	new = 0;
	ex_expansions_tild_split(*line, &left, &right);
	if (ex_expansions_tild_swap(&left) == FAILURE)
		;
	else if (!(new = ft_strjoin(left, right)))
		;
	ft_memdel((void**)&left);
	ft_memdel((void**)&right);
	if (new)
	{
		ft_memdel((void**)&*line);
		*line = new;
	}
}
