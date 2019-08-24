/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:56:35 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 18:56:37 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int				lx_redirect_check(char ch)
{
	if (ch == '<' || ch == '>')
		return (1);
	return (0);
}

int				lx_redirect_get(char *line)
{
	int		len;

	len = 0;
	while (ft_isdigit(line[len]))
		len++;
	if (ft_strncmp(&line[len], "<<", 2) == 0)
		return (add_token(line, len + 2, REDIRECT, DLESS));
	else if (ft_strncmp(&line[len], "<&", 2) == 0)
		return (add_token(line, len + 2, REDIRECT, LESS_AND));
	else if (ft_strncmp(&line[len], "<", 1) == 0)
		return (add_token(line, len + 1, REDIRECT, LESS));
	else if (ft_strncmp(&line[len], ">>", 2) == 0)
		return (add_token(line, len + 2, REDIRECT, DMORE));
	else if (ft_strncmp(&line[len], ">&", 2) == 0)
		return (add_token(line, len + 2, REDIRECT, MORE_AND));
	else if (ft_strncmp(&line[len], ">", 1) == 0)
		return (add_token(line, len + 1, REDIRECT, MORE));
	return (add_token(line, len, WORD, NONE));
}
