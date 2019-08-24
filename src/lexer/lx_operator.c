/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:55:01 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 18:55:07 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int				lx_operator_check(char ch)
{
	if (ch == ';' || ch == '|' || ch == '&')
		return (1);
	return (0);
}

int				lx_operator_get(char *line)
{
	if (ft_strncmp(line, ";", 1) == 0)
		return (add_token(line, 1, OPERATOR, SEMI));
	else if (ft_strncmp(line, "&&", 2) == 0)
		return (add_token(line, 2, OPERATOR, AND_IF));
	else if (ft_strncmp(line, "&", 1) == 0)
		return (add_token(line, 1, OPERATOR, AND));
	else if (ft_strncmp(line, "||", 2) == 0)
		return (add_token(line, 2, OPERATOR, OR_IF));
	else if (ft_strncmp(line, "|", 1) == 0)
		return (add_token(line, 1, OPERATOR, PIPE));
	return (0);
}
