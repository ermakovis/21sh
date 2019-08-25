/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_assignment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:55:13 by tcase             #+#    #+#             */
/*   Updated: 2019/08/25 15:09:13 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int			lx_assignment_check(char *line)
{
	int		len;
	int		eq_pos;

	len = 0;
	while (line[len] && ft_isprint(line[len]) && !ft_isspace(line[len]))
		len++;
	eq_pos = ft_strclen(line, "=");
	if (eq_pos && len >= eq_pos)
		return (1);
	return (0);
}

int			lx_assignment_get(char *line)
{
	int		len;

	len = 0;
	while (line[len] && ft_isprint(line[len]) && !ft_isspace(line[len]))
		len++;
	return (add_token(line, len, ASSIGNMENT, NONE));
}
