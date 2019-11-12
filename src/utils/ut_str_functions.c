/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_str_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:02:50 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 20:24:41 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void		add_str(t_list **list, char *line)
{
	t_list	*new;

	if (!line || !*line)
		return ;
	if (!(new = ft_lstnew(line, ft_strlen(line) + 1)))
		cleanup(-1, "Malloc failed at add_token");
	ft_lstadd_last(list, new);
}

void		printl_str(t_list *list)
{
	ft_printf("%s\n", list->content);
}

void		delete_str(void *content, size_t size)
{
	(void)size;
	ft_memdel(&content);
}
