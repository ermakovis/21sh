/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_input_manipulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:57:08 by tcase             #+#    #+#             */
/*   Updated: 2019/11/07 16:09:51 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void		rl_print_char_search(long ch)
{
	append_char(&g_msh->rl->search_line, (char)ch, PATH_MAX); 
	g_msh->rl->search_pos = 0;
	rl_history_search(ch);
}

void		rl_del_char_search(long ch)
{
	int		len;

	if (!(len = ft_strlen(g_msh->rl->search_line)))
		return ;
	g_msh->rl->search_line[len - 1] = 0;
	g_msh->rl->search_pos = 0;
	rl_history_search(ch);
}


void		rl_print_char(long ch)
{
	t_rl	*rl;

	if (g_msh->rl_mode == SEARCH_MODE)
		return (rl_print_char_search(ch));
	rl = g_msh->rl;
	realloc_check(&(rl->line), rl->line_len);
	ft_printf("%s", g_msh->cmd->insert_mode_on);
	ft_printf("%C", ch);
	if (rl->cur_pos != rl->line_len)
		ft_memmove(&(rl->line[rl->cur_pos + 1]), &(rl->line[rl->cur_pos]),\
				rl->line_len - rl->cur_pos);
	rl->line[rl->cur_pos] = ch;
	rl->line_len++;
	rl->cur_pos++;
	ft_printf("%s", g_msh->cmd->insert_mode_off);
}

void		rl_del_char(long ch)
{
	t_rl	*rl;

	if (!(ch == DELETE || ch == BSPACE))
		return ;
	if (g_msh->rl_mode == SEARCH_MODE)
		return (rl_del_char_search(ch));
	rl = g_msh->rl;
	if (ch == DELETE && rl->cur_pos < rl->line_len)
	{
		ft_memmove(&(rl->line[rl->cur_pos]), &(rl->line[rl->cur_pos + 1]),\
				rl->line_len - rl->cur_pos);
		rl->line[rl->line_len - 1] = 0;
		rl->line_len--;
		ft_printf("%s", g_msh->cmd->del);
	}
	else if (ch == BSPACE && rl->cur_pos > 0 &&\
			rl->line[rl->cur_pos - 1] != '\n')
	{
		ft_memmove(&(rl->line[rl->cur_pos - 1]), &(rl->line[rl->cur_pos]),\
				rl->line_len - rl->cur_pos);
		rl->line[rl->line_len - 1] = 0;
		rl->cur_pos--;
		rl->line_len--;
		ft_printf("%s%s", g_msh->cmd->left, g_msh->cmd->del);
	}
}
