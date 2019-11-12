/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_history_search.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:27:38 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 15:27:56 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int		rl_history_search_calchight(int mode)
{
	int		i;
	int		ret;
	int		line_pos;
	char	*line;
	t_wsize	wsize;

	i = -1;
	ret = 0;
	line = g_msh->rl->line;
	if (mode == RL_MODE)
		line_pos = ft_strlen(find_var(g_msh->env, "PWD"));
	else if (mode == SEARCH_MODE)
		line_pos = ft_strlen(g_msh->rl->search_line) + 29;
	ioctl(0, TIOCGWINSZ, &wsize);
	while (line[++i])
	{
		line_pos++;
		if (line[i] == '\n')
		{
			ret += line_pos / wsize.ws_col + 1;
			line_pos = 0;
		}
	}
	ret += line_pos / wsize.ws_col;
	return (ret);
}

static void		rl_history_search_clear(int mode)
{
	int		hight;

	hight = rl_history_search_calchight(mode);
	while (hight--)
		ft_printf("%s", g_msh->cmd->up);
	ft_printf("%s%s", g_msh->cmd->cur_start, g_msh->cmd->clear_rest);
}

static int		rl_history_search_cycle_action(char *new_line, int pos)
{
	int		len;

	len = ft_strlen(new_line);
	ft_memdel((void**)&g_msh->rl->line);
	if (!(g_msh->rl->line = ft_strnew(MSH_BUFF_SIZE)))
		cleanup(-1, "Malloc failed at rl_history_search_action");
	ft_memcpy(g_msh->rl->line, new_line, len);
	g_msh->rl->line_len = len;
	g_msh->rl->cur_pos = len;
	g_msh->rl->search_pos = pos;
	return (0);
}

static int		rl_history_search_cycle(long ch)
{
	int		i;
	t_list	*list;

	i = 0;
	if (!g_msh->rl->search_line)
		return (0);
	list = g_msh->history;
	while (g_msh->rl->search_pos && i < g_msh->rl->search_pos && ++i)
		list = list->next;
	if (ch == CTRL_R && list->next && ++i)
		list = list->next;
	while (list)
	{
		if (ft_strstr(list->content, g_msh->rl->search_line))
			return (rl_history_search_cycle_action(list->content, i));
		i++;
		list = list->next;
	}
	return (1);
}

void			rl_history_search(long ch)
{
	int		fail;
	char	*line;

	if (!g_msh->history)
		return ;
	rl_history_search_clear(g_msh->rl_mode);
	g_msh->rl_mode = SEARCH_MODE;
	fail = rl_history_search_cycle(ch);
	if (fail)
		ft_printf("(failed)");
	ft_printf("reverse-i-search `%s': %s",\
		g_msh->rl->search_line, g_msh->rl->line);
}
