/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:10:05 by tcase             #+#    #+#             */
/*   Updated: 2019/09/29 15:43:41 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void		ex_env(char ***env)
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

void		ex_tokens(char ***tokens, t_list *list)
{
	char	**ret;
	size_t	size;
	int		i;

	i = 0;
	if (!list)
		return ;
	size = ft_lstsize(list) + 1;
	if (!(ret = (char**)malloc(sizeof(char*) * size)))
		cleanup(-1, "Malloc failed at ex_command_env");
	ft_bzero(ret, sizeof(char*) * size);
	while (list)
	{
		ret[i++] = ft_strdup(((t_token*)list->content)->line);
		list = list->next;
	}
	*tokens = ret;
}

void		ex_command_setpgid(bool bg)
{
	pid_t	pid;

	return ;
	pid = getpid();
	if (bg == 0)
	{
		tcsetpgrp(STDOUT_FILENO, getpid());
		tcsetattr(STDOUT_FILENO, TCSADRAIN, g_msh->original_state); 
	}
	else
		tcsetpgrp(STDOUT_FILENO, g_msh->pid);
}
