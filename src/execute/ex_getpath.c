/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:12:38 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 19:13:26 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int			ex_getpath(char *token, char **cmd)
{
	t_list	*list;
	t_hash	*hash;
	int		i;

	*cmd = 0;
	if (!token || !*token)
		return (FAILURE);
	if (!ft_strchr(token, '/') &&\
		(list = ft_lst_find(g_msh->hash, token, &cmp_hash)))
	{
		hash = list->content;
		(hash->hits)++;
		if (!(*cmd = ft_strdup(hash->command)))
			cleanup(-1, "Malloc failed at ex_getpath");
	}
	else if (!(*cmd = ft_strdup(token)))
			cleanup(-1, "Malloc failed at ex_getpath");
	if (!ut_check_execute(*cmd))
		return (FAILURE);
	return (SUCCESS);
}
