#include "msh.h"

void		lx_alias(t_list **alist)
{
	t_list	*list;
	t_list	*prev;

	list = *alist;
	prev = 0;
	while (list)
	{
		if (!prev)
			*alist = lx_alias_check(alist, list);
		if (((t_token)prev->content)->token_type == OPERATOR)
			prev->next = lx_alist_check(alist, list);
		prev = list;
		list = list->next;
	}
}
