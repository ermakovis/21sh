/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_fc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:55:04 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 16:24:45 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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
		if (!(one = ft_lstnew(list->content,\
			ft_strlen(list->content) + 1)))
			cleanup(-1, "Malloc failed at bin_fc_list_create");
		one->content_size = list->content_size;
		ft_lstadd_last(target, one);
		if (list->content_size == last)
			break ;
		list = list->next;
	}
	if (rev)
		ft_lstrev(target);
	return (1);
}

static int		bin_fc_list_noarg(t_list **target, int flags)
{
	size_t	first;
	size_t	last;

	if (!(flags & BIN_FC_LIST))
		first = g_msh->history->content_size;
	if (flags & BIN_FC_LIST)
		first = bin_fc_list_find_bynum("-10");
	last = g_msh->history->content_size;
	return (bin_fc_list_create(first, last, target));
}

int				bin_fc_list(char **tokens, t_list **target, int flags)
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
		return (bin_fc_list_noarg(target, flags));
	if ((first = bin_fc_list_find(tokens[i])) == -1)
		return (-1);
	if (!tokens[i + 1])
		last = g_msh->history->content_size;
	else if ((last = bin_fc_list_find(tokens[i + 1])) == -1)
		return (-1);
	return (bin_fc_list_create(first, last, target));
}
