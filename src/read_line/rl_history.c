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

/*
**	len - 1 to trim <newline> :(
*/

void	rl_add_history(void)
{
	t_list	*new;
	char	*str;
	int		len;

	if (g_msh->rl->mode == HEREDOC_MODE)
		return ;
	str = g_msh->rl->line;
	if ((len = ft_strlen(str)) == 1)
		return ;
	str[len - 1] = 0;
	if (!str || !*str)
		return ;
	if (!(new = ft_lstnew(str, len)))
		cleanup(-1, "Malloc failed at add_token");
	str[len - 1] = '\n';
	ft_lstadd(&(g_msh->history), new);
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
