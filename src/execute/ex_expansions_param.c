/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_expansions_param.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:18:47 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 20:18:48 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	ex_expansions_param_skip_squote(char **new, char *line)
{
	size_t	i;

	i = 0;
	append_char(new, '\'', NAME_MAX);
	while (line[i] != '\'')
		append_char(new, line[i++], NAME_MAX);
	append_char(new, line[i++], NAME_MAX);
	return (i);
}

static int	ex_expansions_param_skip_bslash(char **new, char *line)
{
	size_t	i;

	i = 0;
	append_char(new, '\\', NAME_MAX);
	append_char(new, line[i++], NAME_MAX);
	return (i);
}

char		*ex_expansions_param_getline(char *param)
{
	t_list *list;

	if ((list = ft_lst_find(g_msh->var, param, &cmp_var)))
		return (((t_var*)list->content)->value);
	else if ((list = ft_lst_find(g_msh->env, param, &cmp_var)))
		return (((t_var*)list->content)->value);
	return (0);
}

static int	ex_expansions_param_find(char *line, char **new)
{
	int	dquote;
	int	i;
	int	ret;

	dquote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			dquote ^= 1;
		if (line[i] == '\\' && (i++))
			i += ex_expansions_param_skip_bslash(new, &(line[i]));
		else if (line[i] == '\'' && !dquote && (i++))
			i += ex_expansions_param_skip_squote(new, &(line[i]));
		else if (line[i] == '$')
		{
			i++;
			if ((ret = ex_expansions_param_replace(new, &(line[i]))) == -1)
				return (EXP_FAILURE);
			i += ret;
		}
		else
			append_char(new, line[i++], NAME_MAX);
	}
	return (SUCCESS);
}

int			ex_expansions_param(char **line)
{
	char	*new;
	int		ret;

	if (!ft_strchr(*line, '$'))
		return (SUCCESS);
	if (!(new = ft_strnew(NAME_MAX)))
		cleanup(-1, "Malloc failed at ex_expansions_param");
	ret = SUCCESS;
	if (ex_expansions_param_find(*line, &new) == EXP_FAILURE)
		ret = EXP_FAILURE;
	ft_memdel((void**)line);
	*line = new;
	return (ret);
}
