#include "msh.h"

static size_t		bin_fc_list_find_bynum(char *line)
{
	int		ret;
	int		max;

	max = g_msh->history->content_size;
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
	if (!(list = g_msh->history->next))
		return (-1);
	line_len = ft_strlen(line);
	while (list)
	{
		if (ft_strnequ(list->content, line, line_len))
			return (list->content_size);
		list = list->next;
	}
	return (-1);
}

static void		bin_fc_list_swap_check(size_t *first, size_t *last, int *rev)
{
	size_t	swap;

	*rev = 0;
	if (*first < *last)
	{
		swap = *last;
		*last = *first;
		*first = swap;
		*rev = 1;
	}
}

static int		bin_fc_list_create(size_t first, size_t last, t_list **target)
{
	t_list	*ret;
	t_list	*one;
	t_list	*list;
	int		rev;

	bin_fc_list_swap_check(&first, &last, &rev);
	list = g_msh->history;
	while (list && list->content_size != first)
		list = list->next;
	while (list)
	{
		add_str(target, list->content);
		if (list->content_size == last)
			break ;
		list = list->next;
	}
	if (rev)
		ft_lstrev(target);
}

int		bin_fc_list(char **tokens, t_list **target)
{
	int		i;
	size_t	first;
	size_t	last;

	i = 1;
	*target = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "-e") && tokens[i + 1])
			i++;
		else if (tokens[i][0] != '-')
			break ;
		else if (tokens[i][0] == '-' && ft_isdigit(tokens[i][1]))
			break ;
		i++;
	}
	if (!tokens[i])
		return (bin_fc_list_create(g_msh->history->content_size,\
			g_msh->history->content_size, target));
	if ((first = bin_fc_list_find(tokens[i])) == -1)
		return (-1);
	if (!tokens[i + 1])
		last = g_msh->history->content_size;
	else if ((last = bin_fc_list_find(tokens[i + 1])) == -1)
		return (-1);
	return (bin_fc_list_create(first, last, target));
}
