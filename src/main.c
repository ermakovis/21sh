/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:21:25 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 20:44:34 by tcase            ###   ########.fr       */
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
				g_msh->shell_name, *str);
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

void				cycle_cleanup(void)
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
	ut_signal_parent();
	display_prompt();
	while (true)
	{
		if (read_line(RL_MODE) == SUCCESS)
		{
			g_msh->tokens = lexer(g_msh->rl->line);
			g_msh->ast = parser(&g_msh->tokens);
			execute(g_msh->ast);
		}
		cycle_cleanup();
		ex_job_state();
		ex_job_print_completed();
		ex_job_del_completed();
		display_prompt();
	}
	cleanup(0, NULL);
}
