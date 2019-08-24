/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:21:25 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 19:24:00 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void			add_flag(char *str)
{
	int		shift;

	shift = 0;
	while (*(++str))
	{
		if ((shift = ft_strchrlen(FLAGS, (*str))) == -1 ||\
			(str[0] == '-' && str[1]))
		{
			ft_dprintf(2, "%s: illegal option -- %c\n",\
				*str, g_msh->shell_name);
			return ;
		}
		g_msh->display_flags |= (1 << shift);
	}
}

static void			parse_params(int *ac, char ***av)
{
	int		count;
	char	**str;

	count = 0;
	str = *av;
	while (++count < *ac && str[count][0] == '-' && str[count][1])
		add_flag(str[count]);
	*av = *av + count;
	*ac = *ac - count;
}

void				handle_sigint(int sig)
{
	(void)sig;
	if (!g_msh->rl->status)
	{
		rl_jump(LINE_END);
		ft_printf("\n");
		display_prompt();
	}
	ft_printf("%s", g_msh->cmd->highlight_mode_off);
	cl_rl_struct();
	init_rl();
}

static void			cycle_cleanup(void)
{
	ft_lstdel(&g_msh->tokens, &del_token);
	pr_ast_del(&g_msh->ast);
	g_msh->tokens = NULL;
	cl_rl_struct();
}

int					main(int argc, char **argv, char **env)
{
	init(env);
	parse_params(&argc, &argv);
	display_prompt();
	signal(SIGINT, handle_sigint);
	while (read_line())
	{
		lexer();
		parser();
		execute(g_msh->ast);
		cycle_cleanup();
		display_prompt();
	}
	cleanup(0, NULL);
}
