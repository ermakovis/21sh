/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:10:41 by tcase             #+#    #+#             */
/*   Updated: 2019/09/28 17:30:29 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H
# include "libft.h"
# include "read_line.h"
# include "lexer.h"
# include "parser.h"
# include "utils.h"
# include "builtin.h"
# include "execute.h"
# include <signal.h>
# include <dirent.h>
# include <limits.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <pwd.h>
# include <sys/types.h>
# include <stdio.h>
# include <uuid/uuid.h>

# define FLAGS "lp"
# define LEXER_V (1 << 0)
# define PARSER_V (1 << 1)

# define SUCCESS 0
# define FAILURE -1

typedef struct winsize	t_wsize;
typedef struct termios	t_term;
typedef struct stat		t_stat;
typedef struct dirent	t_dir;
typedef struct passwd	t_passwd;

typedef struct			s_msh
{
	pid_t				pid;
	int					display_flags;
	int					rl_mode;
	char				*shell_name;
	char				*copy_buffer;
	t_rl				*rl;
	t_cmd				*cmd;
	t_term				*original_state;
	t_ast				*ast;
	t_list				*tokens;
	t_list				*hash;
	t_list				*jobs;
	t_list				*cmd_var;
	t_list				*var;
	t_list				*env;
	t_list				*bin;
	t_list				*alias;
	t_list				*history;
}						t_msh;

t_msh					*g_msh;

/*
**  main.c
**	cycle_cleanup(void)
**	parse_params(int *ac, char **av)
**	add_flag(char *str)
**  handle_sigine(int sig)
*/

#endif
