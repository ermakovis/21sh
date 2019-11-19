/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_history_find.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:34:36 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 15:35:01 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void		lx_history_find_last(char **line)
{
	t_list	*list;
	t_list	*prev;

	prev = 0;
	list = g_msh->history;
	if (list && list->next)
		*line = list->next->content;
}

static void		lx_history_find_bynumber(char **line, int num)
{
	t_list	*list;
	t_list	*rev_tmp;
	int		negative;

	list = g_msh->history;
	negative = 0;
	if (num < 0)
	{
		negative = 1;
		num *= -1;
		num++;
	}
	if (!negative)
	{
		ft_lstrev(&list);
		rev_tmp = list;
	}
	while (list && --num)
		list = list->next;
	if (!num && list)
		*line = list->content;
	if (!negative)
		ft_lstrev(&rev_tmp);
}

static void		lx_history_find_byword(char **line, char *word)
{
	t_list	*list;
	int		word_len;

	if (!word && !*word)
		return ;
	word_len = ft_strlen(word);
	list = g_msh->history;
	while (list)
	{
		if (ft_strnequ(list->content, word, word_len))
		{
			*line = list->content;
			return ;
		}
		list = list->next;
	}
}

t_list			*lx_history_find(t_list *list, char **line)
{
	t_token	*token;

	while (list)
	{
		token = list->content;
		if (!ft_strcmp(token->line, "!!"))
		{
			lx_history_find_last(line);
			return (list);
		}
		if (token->line[0] == '!' && ft_isnumber(&token->line[1]))
		{
			lx_history_find_bynumber(line, ft_atoi(&token->line[1]));
			return (list);
		}
		if (token->line[0] == '!' && token->line[1] && token->line[1] != '=')
		{
			lx_history_find_byword(line, &token->line[1]);
			return (list);
		}
		list = list->next;
	}
	return (NULL);
}
