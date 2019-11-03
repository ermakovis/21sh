#include "msh.h"

static size_t		bin_fc_list_find_bynum(char *line)
{
	int		ret;
	int		max;

	max = g_msh->history->content_size - 1;
	ret = ft_atoi(line);
	if (ret <= 0 && max + ret <= 0)
		ret = 1;
	else if (ret <= 0)
		ret = max + ret;
	else if (ret > 0 && ret >= max)
		ret = max;
	return ((size_t)ret);

}

static size_t	bin_fc_list_find(char *line)
{
	t_list	*list;
	int		line_len;

	if (!line)
		return (g_msh->history->content_size);
	if (ft_isnumber(line))
		return (bin_fc_list_find_bynum(line));
	list = g_msh->history;
	line_len = ft_strlen(line);
	while (list)
	{
		if (ft_strnequ(list->content, line, line_len))
			return (list->content_size);
		list = list->next;
	}
	return (-1);
}

int		bin_fc_list(char **tokens, t_list **target)
{
	int		i;
	size_t	first;
	size_t	last;

	i = 0;
	while (tokens[++i])
	{
		if (!ft_strcmp(tokens[i], "-e") && tokens[i + 1])
			i++;
		if (tokens[i][0] != '-')
			break ;
	}
	if ((first = bin_fc_list_find(tokens[i])) == -1)
		return (-1);
	if ((last = bin_fc_list_find(tokens[i + 1])) == -1)
		return (-1);
}
