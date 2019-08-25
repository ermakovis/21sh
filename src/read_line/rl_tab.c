/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 20:36:53 by tcase             #+#    #+#             */
/*   Updated: 2019/08/25 13:53:46 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void			rl_tab_lastword(char **word, int *word_num)
{
	int		i;
	char	*str;

	i = 0;
	str = g_msh->rl->line;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i])
		{
			*word = &str[i];
			(*word_num)++;
		}
		while (str[i] && str[i] != ' ')
			i++;
	}
}

static char		rl_tab_check_char(void)
{
	t_list		*tmp_list;
	int			line_len;
	char		*str;
	char		ch;

	rl_tab_lastword(&str, &line_len);
	line_len = ft_strlen(str);
	ch = ((char*)g_msh->rl->tab_items->content)[line_len];
	tmp_list = g_msh->rl->tab_items;
	while (tmp_list)
	{
		str = tmp_list->content;
		if (str[line_len] != ch)
			return (0);
		tmp_list = tmp_list->next;
	}
	return (ch);
}

void			rl_tab(long ch)
{
	char	nch;

	nch = 0;
	if (ch != TAB)
		return ;
	if (!g_msh->rl->line)
		return ;
	if (rl_tab_create_list() == FAILURE)
		return ;
	ft_lst_sort(&(g_msh->rl->tab_items), &ft_strcmp);
	while ((nch = rl_tab_check_char()))
		rl_print_char(nch);
	if (ft_lstsize(g_msh->rl->tab_items) == 1 &&\
			!ft_strcmp(g_msh->rl->tab_items->content, g_msh->rl->line))
		rl_print_char(' ');
	ft_lstdel(&(g_msh->rl->tab_items), &delete_str);
}
