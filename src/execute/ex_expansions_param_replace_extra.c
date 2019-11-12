/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_expansions_param_replace_extra.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:57:16 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 19:58:02 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	ex_exp_param_split_simple(char **param, char *line)
{
	int	len;

	len = 0;
	while (line[len] && !ft_strchr("\n\t\'\"\\\t |$;}", line[len]))
		len++;
	if (!(*param = ft_strndup(line, len)))
		cleanup(-1, "Malloc failed at ex_exp_param_split_simple");
	return (len);
}

int	ex_exp_param_return(char *param, char *word, int ret)
{
	ft_memdel((void**)&param);
	ft_memdel((void**)&word);
	return (ret);
}
