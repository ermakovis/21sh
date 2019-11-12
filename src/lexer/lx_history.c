/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:33:42 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 15:33:54 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void		lx_history_replace(t_list **alist)
{
	char	*line;
	char	*tmp;
	t_token	*token;
	t_list	*list;

	list = *alist;
	line = 0;
	tmp = 0;
	while (((t_token*)list->content)->token_type != NEWLINE)
	{
		token = list->content;
		if (line)
		{
			tmp = line;
			line = ft_strjoin(line, " ");
			ft_memdel((void**)&tmp);
		}
		tmp = line;
		line = ft_strjoin(line, token->line);
		ft_memdel((void**)&tmp);
		list = list->next;
	}
	ft_memdel((void**)&g_msh->history->content);
	g_msh->history->content = line;
}

static void		lx_history_insert(t_list **alist, t_list *list, t_list *tokens)
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

void			lx_history(t_list **alist)
{
	int		found;
	char	*line;
	t_list	*list;
	t_list	*tokens;

	found = 0;
	line = 0;
	while ((list = lx_history_find(*alist, &line)))
	{
		found = 1;
		if (!(tokens = lx_tokens(line)))
			ft_lst_remove(alist, list, &del_token);
		else
			lx_history_insert(alist, list, tokens);
	}
	if (found)
		lx_history_replace(alist);
}
