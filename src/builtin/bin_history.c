/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:51:35 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 15:51:37 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int		bin_history(t_list *list)
{
	t_list	*tmp;

	list = g_msh->history;
	ft_lstrev(&list);
	tmp = list;
	while (list)
	{
		ft_printf("%5zu  %s\n", list->content_size, list->content);
		list = list->next;
	}
	ft_lstrev(&tmp);
	return (BIN_SUCCESS);
}
