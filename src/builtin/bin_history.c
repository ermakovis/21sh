#include "msh.h"

int		bin_history(t_list *list)
{
	int		i;
	t_list	*tmp;

	i = 1;
	list = g_msh->history;
	ft_lstrev(&list);
	tmp = list;
	while (list)
	{
		ft_printf("%-10d%s\n", i, list->content);
		i++;
		list = list->next;
	}
	ft_lstrev(&tmp);
	return (BIN_SUCCESS);
}
