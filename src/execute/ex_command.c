/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:10:05 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 19:11:20 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void		ex_env(char ***env)
{
	t_list	*env_list;
	char	**ret;
	size_t	size;
	int		i;

	i = 0;
	if (!(env_list = g_msh->env))
		return ;
	size = ft_lstsize(env_list) + 1;
	if (!(ret = (char**)malloc(sizeof(char*) * size)))
		cleanup(-1, "Malloc failed at ex_command_env");
	ft_bzero(ret, sizeof(char*) * size);
	while (env_list)
	{
		ret[i++] = var_to_str(env_list->content);
		env_list = env_list->next;
	}
	*env = ret;
}

int				ex_command(t_ast *ast)
{
	char	**tokens;
	char	**env;
	char	*cmd;
	int		ret;

	cmd = NULL;
	ex_redirections(ast->token);
	ex_env(&env);
	ex_tokens(ast->token, &tokens);
	if (ex_getpath(tokens[0], &cmd) == FAILURE)
		ret = FAILURE;
	else if (ex_check_executable(cmd) == FAILURE)
		ret = FAILURE;
	else if ((ret = execve(cmd, tokens, env) == -1))
		ft_dprintf(2, "%s: launch failed\n", cmd);
	ft_memdel((void**)&cmd);
	ft_free_table(&env);
	ft_free_table(&tokens);
	return (ret);
}
