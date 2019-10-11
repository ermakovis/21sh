#include "msh.h"

static int		lx_alias_recursion_protection(t_list **alist, char *line)
{
	t_list	*list;
	t_token *token;

	list = *alist;
	while (list)
	{
		token = list->content;
		ft_printf("%s %s\n", token->alias, line);
		if (ft_strequ(token->alias, line))
			return (false);
		list = list->next;
	}
	return (true);
}

static t_list	*lx_alias_find(t_list **alist, char **line)
{
	t_list	*list;
	t_list	*prev;
	t_token	*token;

	prev = 0;
	list = *alist;
	while (list)
	{
		if (!prev || ((t_token*)prev->content)->token_type == OPERATOR)
		{
			token = list->content;
			while (list && token->token_type == ASSIGNMENT)
				list = list->next;
			token = list->content;
			if (lx_alias_recursion_protection(alist, token->line))
				if ((*line = find_var(g_msh->alias, token->line)))
					return (list);
		}
		prev = list;
		list = list->next;
	}
	return (0);
}

static void		lx_alias_insert(t_list **alist, t_list *list, t_list *tokens)
{
	t_list	*tmp;
	t_list	*tokens_last;

	tokens_last = tokens;
	while (tokens_last->next)
		tokens_last = tokens_last->next;
	if (list == *alist)
	{
		tokens_last->next = (*alist)->next;
		*alist = tokens;
	}
	else
	{
		tmp = *alist;
		while (tmp && tmp->next != list)
			tmp = tmp->next;
		tokens_last->next = tmp->next->next;
		tmp->next = tokens;
	}
	ft_lstdelone(&list, &del_token);
}

static void		lx_alias_mark_tokens(t_list *list, char *line)
{
	while (list)
	{
		((t_token*)list->content)->alias = ft_strdup(line);
		list = list->next;
	}
}

void		lx_alias(t_list **alist)
{
	t_list	*list;
	t_list	*tokens;
	char	*line;

	if (!(list = lx_alias_find(alist, &line)))
		return ;
	if (!(tokens = lx_tokens(line)))
	{
		ft_lst_remove(alist, list, &del_token);
		return (lx_alias(alist));
	}
	lx_alias_mark_tokens(tokens, ((t_token*)list->content)->line);
	lx_alias_insert(alist, list, tokens);
	lx_alias(alist);
}
