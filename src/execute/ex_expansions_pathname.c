#include "msh.h"

static bool	ex_exp_pathname_split(char *line, char **path, char **pat)
{
	size_t	i;
	size_t	len;
	char	*ret;

	i = -1;
	len = 0;
	*path = 0;
	*pat = 0;
	while (line[++i])
		if (line[i] == '/')
			len = i;
	if (!line[len + 1])
		return (false);
	if (len)	
		if (!(*path = ft_strndup(line, len + 1)))
			cleanup (-1, "Malloc failed at get_path");
	if (!(*pat = ft_strdup(line + len + (len ? 1 : 0))))
		cleanup (-1, "Malloc failed at get_path");
	return (true);
}

static t_list	*ex_exp_pathname_cycle(DIR *dir, char *path, char *pat)
{
	t_dir	*entry;
	t_list	*list;
	char	*join_line;

	list = 0;
	while ((entry = readdir(dir)))
	{
		if (ft_strcmp(entry->d_name, "..") &&\
				ft_strcmp(entry->d_name, ".") &&\
				ex_globbing(entry->d_name, pat, 0, 0))
		{
			if (!(join_line = ft_strjoin(path, entry->d_name)))
				cleanup(-1, "Malloc failed at ex_exp_pathname_cycle");
			add_token(&list, join_line, WORD, NONE);
		}
	}
	if (list)
		ft_lst_sort(&list, &cmp_token);
	return (list);
}

static void	ex_exp_pathname_insert(t_list **alist, t_list **list, t_list *new)
{
	t_list	*tmp;

	tmp = new;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (*alist)->next;
	(*alist)->next = new;
	ft_lst_remove(alist, *list, &del_token);
	*list = tmp;
}

static int	ex_exp_pathname_getdir(char *path, DIR **dir)
{
	if (!path)
		if (!(*dir = opendir(".")))
			return (FAILURE);
	if (path && *path)
		if (!(*dir = opendir(path)))
			return (FAILURE);
	return (SUCCESS);	
}

void		ex_expansions_pathname(t_list **alist, t_list **list)
{
	char	*path;
	char	*pat;
	DIR		*dir;
	t_token	*token;
	t_list	*new_list;

	token = (*list)->content;
	if (!token->line)
		return ;
	if (!(ex_exp_pathname_split(token->line, &path, &pat)))
		return ;	
	if (ex_exp_pathname_getdir(path, &dir) == SUCCESS)
		if ((new_list = ex_exp_pathname_cycle(dir, path, pat)))
			ex_exp_pathname_insert(alist, list, new_list);
	if (dir)
		closedir(dir);
	ft_memdel((void**)&path);
	ft_memdel((void**)&pat);
}
