/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd_canon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:07:23 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 16:07:23 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int bin_cd_canon_dotdot_l(char **line, int *i)
{
	(*i)++;
	return (1);
}

static int bin_cd_canon_dotdot_p(char **line, int *i)
{
	char	*tmp;

	if (!(tmp = ft_strndup(*line, *i)))
		cleanup(-1, "Malloc failed at bin_cd_canon_dotdot_p");
	(*i)++;
	return (1);
}

int		bin_cd_canon(char **path, int flag)
{
	char	*line;
	int		i;

	i = 0;
	if (!(line = ft_strdup(*path)))
		cleanup(-1, "Malloc failed at bin_cd_canon");
	while (line[i])
	{
		if (line[i] == '/' && line[i + 1] == '/')
			ft_memmove(&line[i], &line[i + 1], ft_strlen(&line[i + 1]) + 1);
		else if (ft_strnequ(&line[i], "/./", 3) || ft_strequ(&line[i], "/."))
			ft_memmove(&line[i], &line[i + 2], ft_strlen(&line[i + 2]) + 1);
		else if (ft_strnequ(&line[i], "/../", 4) || ft_strequ(&line[i], "/.."))
		{
			if (flag & BIN_CD_P && !bin_cd_canon_dotdot_p(&line, &i))	
				return (BIN_FAILURE);
			else if (!bin_cd_canon_dotdot_l(&line, &i))
				return (BIN_FAILURE);	
		}
		else
			i++;
	}
	ft_memdel((void**)path);
	*path = line;
	return (BIN_SUCCESS);
}
