/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:48:44 by tcase             #+#    #+#             */
/*   Updated: 2019/08/10 21:30:13 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "read_line.h"

int				get_char(long *ch)
{
	read(STDIN_FILENO, ch, sizeof(long));
	return (1);
}

void			init_rl(void)
{
	t_rl	*new_rl;
	size_t	size;

	size = sizeof(t_rl);
	if (!(new_rl = (t_rl*)malloc(size)))
		cleanup(-1, "Failed to malloc for rl structure\n");
	ft_bzero(new_rl, size);
	if (!(new_rl->line = ft_strnew(MSH_BUFF_SIZE)))
		cleanup(-1, "Failed to malloc for rl's new string\n");
	new_rl->history = -1;
	g_msh->rl = new_rl;
}

static int		rl_quotes_check(void)
{
	int		i;
	int		dquote;
	int		squote;
	char	*line;

	i = -1;
	dquote = 0;
	squote = 0;
	line = g_msh->rl->line;
	while (line[++i])
	{
		if (line[i] == '\\' && squote == 0)
			i++;
		else if (line[i] == '\'' && dquote == 0)
			squote ^= 1;
		else if (line[i] == '\"' && squote == 0)
			dquote ^= 1;
	}
	if (dquote)
		ft_printf("\ndquote> ");
	if (squote)
		ft_printf("\nsquote> ");
	return (!dquote && !squote);
}

static void		rl_switch(long ch)
{
	rl_tab(ch);
	rl_history(ch);
	rl_move_cur(ch);
	rl_jump(ch);
	rl_del_char(ch);
	if (ft_isprint(ch))
		rl_print_char(ch);
}

/*
**	need newline to be on the end of input
*/
int				read_line(void)
{
	long	ch;

	ch = 0;
	init_rl();
	set_terminal_raw();
	while (get_char(&ch))
	{
		if ((ch == '\n' && rl_quotes_check()))
		{
			g_msh->rl->cur_pos = g_msh->rl->line_len;
			rl_print_char('\n');
			g_msh->rl->status = 1;
			break ;
		}
		rl_switch(ch);
		ch = 0;
	}
	set_terminal_canon();
	rl_add_history();
	return (g_msh->rl->status);
}
