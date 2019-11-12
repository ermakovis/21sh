/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unalias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:40:42 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 15:40:49 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	bin_unalias_usage(void)
{
	ft_dprintf(2, "unalias: usage: unalias [-a] name [name...]\n");
	return (BIN_FAILURE);
}

static int	bin_unalias_fullclean(void)
{
	ft_lstdel(&g_msh->alias, &delete_var);
	return (BIN_SUCCESS);
}

int			bin_unalias(t_list *list)
{
	size_t	tokens_count;
	char	**tokens;
	int		i;
	int		ret;

	ret = BIN_SUCCESS;
	tokens_count = ft_lstsize(list);
	if (tokens_count == 1)
		return (bin_unalias_usage());
	if (tokens_count > 1 &&\
		!ft_strcmp(((t_token*)list->next->content)->line, "-a"))
		return (bin_unalias_fullclean());
	i = 0;
	ex_tokens(&tokens, list);
	while (tokens[++i])
	{
		if (find_var(g_msh->alias, tokens[i]))
			ft_lst_remove_if(&g_msh->alias, tokens[i],\
					&cmp_var, &delete_var);
		else
			ft_dprintf(2, "%s: unalias: %s\n", g_msh->shell_name, tokens[i]);
	}
	ft_free_table(&tokens);
	return (ret);
}
