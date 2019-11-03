/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:53:04 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 21:37:07 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void rl_history_trim(void)
{
	t_list	*list;
	t_list	*rev;
	int		lst_size;

	list = g_msh->history;
	if ((lst_size = ft_lstsize(list)) < HISTORY_MAX)
		return ;
	ft_lstrev(&list);
	rev = list;
	while (lst_size > HISTORY_MAX)
	{
		ft_lstpop(&list, &delete_str);
		lst_size--;
	}
	ft_lstrev(&list);
}

static int rl_history_valid(char *line)
{
	int		i;
	int		only_spaces;
	int		newline_pos;
	char	store;
	int		ret;

	i = -1;
	only_spaces = 1;
	ret = SUCCESS;
	while (line[++i] && line[i] != '\n')
		if (!ft_isspace(line[i]))
			only_spaces = 0;
	if (only_spaces)
		ret = FAILURE;
	newline_pos = ft_strlen(line) - 1;
	store = line[newline_pos];
	line[newline_pos] = 0;
	if (g_msh->history && \
		!(ft_strcmp(g_msh->history->content, line)))
		ret = FAILURE;
	line[newline_pos] = store;
	return (ret);

}

void		rl_history_putnumbers(void)
{
	t_list	*list;
	t_list	*rev;
	int		i;

	i = 1;
	list = g_msh->history;
	ft_lstrev(&list);
	rev = list;
	while (list)
	{
		list->content_size = i;
		i++;
		list = list->next;
	}
	ft_lstrev(&rev);
}

void	rl_add_history(void)
{
	t_list	*new;
	char	*str;
	int		len;

	if (g_msh->rl->mode == HEREDOC_MODE)
		return ;
	str = g_msh->rl->line;
	if (rl_history_valid(str) == FAILURE)
		return ;
	if ((len = ft_strlen(str)) == 1)
		return ;
	str[len - 1] = 0;
	if (!str || !*str)
		return ;
	if (!(new = ft_lstnew(str, len)))
		cleanup(-1, "Malloc failed at add_token");
	str[len - 1] = '\n';
	ft_lstadd(&(g_msh->history), new);
	rl_history_trim();
	rl_history_putnumbers();
}

void	rl_history(long ch)
{
	t_rl	*rl;
	int		size;

	if (!(ch == UP || ch == DOWN))
		return ;
	if (!g_msh->history || !g_msh->history->content)
		return ;
	rl = g_msh->rl;
	size = ft_lstsize(g_msh->history) - 1;
	if (ch == UP && rl->history < size)
		rl_history_change(++(rl->history));
	else if (ch == DOWN && rl->history >= 0)
		rl_history_change(--(rl->history));
}
