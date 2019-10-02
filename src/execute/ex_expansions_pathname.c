#include "msh.h"

static bool	ex_exp_pathname_split(char *line, char **path, char **pat)
{
	size_t	i;
	size_t	len;
	char	*ret;

	i = -1;
	len = 0;
	if (!(ft_strchr(line, '/')))
	{
		if (!(*path = ft_strdup("./")))
			cleanup (-1, "Malloc failed at get_path");
		if (!(*pat = ft_strdup(line)))
			cleanup (-1, "Malloc failed at get_path");
		return (true);
	}
	while (line[++i])
		if (line[i] == '/')
			len = i;
	if (!line[len + 1])
		return (false);
	if (!(*path = ft_strndup(line, len + 1)))
		cleanup (-1, "Malloc failed at get_path");
	if (!(*pat = ft_strdup(line + len + 1)))
		cleanup (-1, "Malloc failed at get_path");
	return (true);
}

void		ex_expansions_pathname(t_token *token)
{
	char	*path;
	char	*pat;
	char	*ret;
	DIR		*dir;
	t_dir	*entry;

	if (!token->line)
		return ;
	if (!(ex_exp_pathname_split(token->line, &path, &pat)))
		return ;	
	if ((dir = opendir(path)))
	{
		while ((entry = readdir(dir)))
		{
			if (ex_globbing(entry->d_name, pat, 0, 0))
			{
				ft_printf("%s%s\n", path, entry->d_name);	
			}

		}
	}
	ft_strdel(&path);
	ft_strdel(&pat);
}
