/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:05:51 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 18:49:31 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static	void	init_cmd_fill(t_cmd *cmd)
{
	char *cmd_buff;

	cmd_buff = cmd->area;
	cmd->start = tgetstr("cr", &cmd_buff);
	cmd->clear_line = tgetstr("ce", &cmd_buff);
	cmd->clear_rest = tgetstr("cd", &cmd_buff);
	cmd->cur_start = tgetstr("cr", &cmd_buff);
	cmd->up = tgetstr("up", &cmd_buff);
	cmd->down = tgetstr("do", &cmd_buff);
	cmd->left = tgetstr("le", &cmd_buff);
	cmd->right = tgetstr("nd", &cmd_buff);
	cmd->del = tgetstr("dc", &cmd_buff);
	cmd->highlight_mode_on = tgetstr("so", &cmd_buff);
	cmd->highlight_mode_off = tgetstr("se", &cmd_buff);
	cmd->insert_mode_on = tgetstr("im", &cmd_buff);
	cmd->insert_mode_off = tgetstr("ei", &cmd_buff);
}

static void		init_cmd(void)
{
	t_cmd	*cmd;
	char	*cmd_buff;
	char	buffer[MSH_BUFF_SIZE];

	if (!(cmd_buff = ft_strnew(MSH_CMD_BUFF)))
		cleanup(-1, "Malloc failed at init_term_command");
	if (tgetent(buffer, find_var(g_msh->env, "TERM")) < 0)
		cleanup(-1, "Failed to get terminfo at init_term");
	if (!(cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		cleanup(-1, "Failed to malloc for command structure");
	ft_bzero(cmd, sizeof(t_cmd));
	cmd->area = cmd_buff;
	init_cmd_fill(cmd);
	g_msh->cmd = cmd;
}

static void		init_msh(void)
{
	t_msh	*new_msh;

	if (!(new_msh = (t_msh*)malloc(sizeof(t_msh))))
		cleanup(-1, "Failed to malloc for main structure");
	ft_bzero(new_msh, sizeof(t_msh));
	new_msh->shell_name = ft_strdup("42sh");
	g_msh = new_msh;
}

static void		init_orig_state(void)
{
	t_term	*orig;

	if (!(orig = (t_term*)malloc(sizeof(t_term))))
		cleanup(-1, "Failed to malloc for terminal state structure");
	while (tcgetpgrp(STDOUT_FILENO) != (g_msh->pid = getpgrp()))
		kill(-g_msh->pid, SIGTTIN);
	g_msh->pid = getpid();
	if (setpgid(g_msh->pid, g_msh->pid) < 0)
		cleanup(-1, "Couldn't put shell in its own process group");
	if (tcsetpgrp(STDOUT_FILENO, g_msh->pid) == -1)
		cleanup(-1, "Couldn't get control of terminal");
	if (tcgetattr(STDOUT_FILENO, orig) == -1)
		cleanup(-1, "Failed to save terminal original state");
	g_msh->original_state = orig;
}

void			init(char **env)
{
	init_msh();
	init_env(env);
	init_bins();
	init_cmd();
	init_orig_state();
	init_alias();
	init_hash();
	init_history();
}
